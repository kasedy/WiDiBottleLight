#include "LightState.h"

void LightState::setup() {
  for (int i = 0; i < getLedCount(); ++i) {
    for (int gpio : lightLanes[i].gpio) {
      pinMode(gpio, OUTPUT);
      setPinValue(i, 0);
    }
  }
}

void LightState::setPinValue(uint8_t pinIndex, uint8_t brightness) {
  int pwmDuty = map(brightness, 0, 255, 0, 1023);
  for (int gpio : lightLanes[pinIndex].gpio) {
    analogWrite(gpio, pwmDuty);
  }
  lightLanes[pinIndex].brightness = brightness;
}

void LightState::setAllPinValue(uint8_t brightness) {
  for (uint8_t i = 0; i < getLedCount(); ++i) {
    setPinValue(i, brightness);
  }    
}