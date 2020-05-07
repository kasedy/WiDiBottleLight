#pragma once

#include "animations/RandomSplashes.h"

#include <stdint.h>
#include <vector>

class RandomAsynchronousSplashes : public RandomSplashes {
private:
  struct LedInfo {
    uint8_t brightnessSettingsIndex;
    unsigned long timeToChangeBrightness;
  };

  LedInfo *ledInfo;
  void resetTimers(unsigned long timeToChangeBrightness);
  BrightnessSettings nextBrightness(uint8_t index);
public:
  constexpr static uint8_t pinsRequires = 1;

  RandomAsynchronousSplashes(
    LightController *lightController, 
    int8_t speed = 0);
  RandomAsynchronousSplashes(
    LightController *lightController, 
    std::vector<BrightnessSettings> brightnessSettings,
    int8_t speed = 0);
  virtual ~RandomAsynchronousSplashes();
  virtual void handle() override;
};
