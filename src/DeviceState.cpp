#include "DeviceState.h"

#include "animations/NoAnimation.h"

DeviceState::DeviceState(const std::vector<Effect>& effects) :
    effects(effects) {
  if (effects.empty()) {
    currentAnimation = new NoAnimation(nullptr);
  } else {
    setAnimationByIndex(0);
  }
}

void DeviceState::nextAnimation() {
  uint8_t animationIndex = getCurrentAnimationIndex();
  if (++animationIndex >= effects.size()) {
    animationIndex = 0;
  }
  setAnimationByIndex(animationIndex);
}

void DeviceState::setAnimationByIndex(uint8_t animationIndex) {
  if (currentAnimationIndex == animationIndex 
      || animationIndex >= effects.size()) {
    return;
  }
  if (currentAnimation) {
    delete currentAnimation;
  }
  const Effect &effectInfo = effects[animationIndex];
  currentAnimation = effectInfo.animationBuilder(nullptr);
  effectChanged = true;
  currentAnimationIndex = animationIndex;
}

void DeviceState::setAnimationByName(const char* effectName) {
  for (size_t animationIndex = 0; animationIndex < effects.size(); ++animationIndex) {
    if (strcmp(effects[animationIndex].name, effectName) == 0) {
      setAnimationByIndex(animationIndex);
      return;
    }
  }
}