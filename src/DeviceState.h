#pragma once

#include "animations/BaseAnimation.h"

#include <Esp.h>

template<class T>
bool updateField(T& current, const T& newValue) {
  if (current == newValue) {
    return false;
  }
  current = newValue;
  return true;
}

class DeviceState {
  const std::vector<Effect> effects;
  BaseAnimation *currentAnimation = nullptr;
  uint8_t currentAnimationIndex = -1;
  uint8_t lightBrightness = 255;
  uint8_t animationSpeed = 255 / 2;
  bool stateOn:1;
 
  bool effectChanged:1;
  bool lightBrightnessChanged:1;
  bool animationSpeedChanged:1;
  bool stateOnChanged:1;

public:
  DeviceState(const std::vector<Effect>& effects);

  inline size_t getAnimationCount() const { return effects.size(); }
  inline uint8_t getCurrentAnimationIndex() const { return currentAnimationIndex; }
  inline const char* getAnimationName(size_t index) const { return effects[index].name; }
  inline const char* getCurrentAnimationName() const { return effects[currentAnimationIndex].name; }
  void nextAnimation();
  void setAnimationByIndex(uint8_t animationIndex);
  void setAnimationByName(const char* effectName);

  inline uint8_t getLightBrightness() const { return lightBrightness; }
  inline void setLightBrightness(uint8_t newLightBrightness) { 
    lightBrightnessChanged |= updateField(lightBrightness, newLightBrightness); 
  }

  inline uint8_t getAnimationSpeed() const { return animationSpeed; }
  inline void setAnimationSpeed(uint8_t newAnimationSpeed) { 
    animationSpeedChanged |= updateField(animationSpeed, newAnimationSpeed); 
  }

  inline  bool isOn() const { return stateOn; }
  inline void toggleState() { setStateOn(!isOn()); }
  inline void setStateOn(bool newStateOn) { 
    if (stateOn == newStateOn) {
      return;
    }
    stateOn = newStateOn;
    stateOnChanged = true;
  }

  inline bool isEffectChanged() const { return effectChanged; }
  inline bool isMaxBrightensChanged() const { return lightBrightnessChanged; }
  inline bool isAnimationSpeedChanged() const { return animationSpeedChanged; }
  inline bool isStateOnChanged() const { return stateOnChanged; }
  inline bool isChanged() const {
    return isMaxBrightensChanged() 
        || isStateOnChanged() 
        || isEffectChanged() 
        || isAnimationSpeedChanged();
  }
  inline void reset() {
    effectChanged = false;
    lightBrightnessChanged = false;
    animationSpeedChanged = false;
    stateOnChanged = false;
  }
};