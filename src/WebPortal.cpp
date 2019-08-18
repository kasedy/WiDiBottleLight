#include <WebPortal.h>
#include "config.h"
#include "dbg.h"
#include "LightController.h"
#include "generated/webportal.html.gz.h"

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

extern LightController *lightController;

const char *STATE_PARAM PROGMEM = "state";
const char *BRIGHTNESS_PARAM PROGMEM = "brightness";
const char *SPEED_PARAM PROGMEM = "speed";
const char *EFFECT_PARAM PROGMEM = "effect";

namespace WebPortal {
  AsyncWebServer *server;
  AsyncWebSocket *ws;

  AsyncWebSocketMessageBuffer *getLightStateJson() {
    StaticJsonDocument<528> jsonBuffer;
    jsonBuffer[FPSTR(STATE_PARAM)] = lightController->isOn();
    jsonBuffer[FPSTR(BRIGHTNESS_PARAM)] = lightController->getLightBrightness();
    jsonBuffer[FPSTR(SPEED_PARAM)] = lightController->getAnimationSpeed();
    jsonBuffer[FPSTR(EFFECT_PARAM)] = lightController->getCurrentAnimationIndex();
    JsonObject effectOptions = jsonBuffer.createNestedObject(F("options"))
        .createNestedObject(FPSTR(EFFECT_PARAM));
    for (size_t index = 0; index < lightController->getAnimationCount(); ++index) {
      effectOptions[String(index)] = lightController->getAnimationName(index);
    }
    size_t len = measureJson(jsonBuffer); // len without null terminating char
    AsyncWebSocketMessageBuffer *websocketBuffer = ws->makeBuffer(len); //  creates a buffer (len + 1) for you.
    if (websocketBuffer) {
      serializeJson(jsonBuffer, (char *)websocketBuffer->get(), len + 1);
    }
    return websocketBuffer;
  }

  void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
    if (type == WS_EVT_CONNECT) {
      client->text(getLightStateJson());
    } else if (type == WS_EVT_DATA){
      AwsFrameInfo * info = (AwsFrameInfo*)arg;
      String msg = "";
      if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT){
        StaticJsonDocument<528> jsonBuffer;
        char buffer[len + 1];
        buffer[len] = '\0';
        memcpy(buffer, data, len);
        DeserializationError error = deserializeJson(jsonBuffer, buffer);
        if (!error) {
          bool state = jsonBuffer[FPSTR(STATE_PARAM)];
          int brightness = jsonBuffer[FPSTR(BRIGHTNESS_PARAM)];
          int speed = jsonBuffer[FPSTR(SPEED_PARAM)];
          int effectIndex = jsonBuffer[FPSTR(EFFECT_PARAM)];
          lightController->setStateOn(state);
          lightController->setLightBrightness(brightness);
          lightController->setAnimationSpeed(speed);
          lightController->setAnimationByIndex(effectIndex);
          DBG("WEB PORTAL! state: %s; brightness: %d; speed: %d; effect: %d\n", state ? "true" : "false", brightness, speed, effectIndex);          
        }
      }
    }
  }

  void setup() {
    server = new AsyncWebServer(80);
    ws = new AsyncWebSocket(F("/ws"));
    server->on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, F("text/plain"), String(ESP.getFreeHeap()));
    });
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", webportal_html_gz, webportal_html_gz_len);
      response->addHeader("Content-Encoding", "gzip");
      response->addHeader("X-XSS-Protection", "1; mode=block");
      response->addHeader("X-Content-Type-Options", "nosniff");
      response->addHeader("X-Frame-Options", "deny");
      request->send(response);
    });
    server->onNotFound([](AsyncWebServerRequest *request){
      request->redirect("/");
    });
    ws->onEvent(onWsEvent);
    server->addHandler(ws);
    server->begin();
  }

  void broadcaseLightChanges() {
    ws->textAll(getLightStateJson());
  }
}