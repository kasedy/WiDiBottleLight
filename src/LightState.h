#pragma once

#include <ESP.h>

class LightState {
  struct LineState {
    inline LineState(uint8_t gpio) : gpio(1, gpio), brightness(0) {}
    inline LineState(std::initializer_list<uint8_t> gpio) : gpio(gpio), brightness(0) {}
    const std::vector<uint8_t> gpio;
    uint8_t brightness;
  };

  std::vector<LineState> lightLanes;
public:
  inline LightState(const std::vector<LineState> &pinsGpio) : lightLanes(pinsGpio) {}

  void setup();

  inline uint8_t getLedCount() const { return lightLanes.size(); }
  inline uint8_t getLedBrightness(uint8_t pinIndex) const { return lightLanes[pinIndex].brightness; }

   void setPinValue(uint8_t pinIndex, uint8_t brightness);
   void setAllPinValue(uint8_t brightness);
};