#pragma once

#include <vector>
#include <animations/all.h>

#include <functional>
#include <tuple>
using namespace std;

template<class T, typename... Args>
BaseAnimation* constructor(LightController *lightController, Args... args) {
  return new T(lightController, args...);
}

template<class T, class... Args>
Effect makeEffect(const char *name, Args&&... args) {
  auto bound = std::bind(&constructor<T, Args...>, std::placeholders::_1, std::forward<Args>(args)...);
  return {name, bound, T::pinsRequires};
}

Effect noAnimation() {
  return makeEffect<NoAnimation>("No animation");
}

Effect effectFadeOnSwitch() {
  return makeEffect<FadeSwitch>("Fade on switch");
}

Effect effectFadeInCycle() {
  return makeEffect<FadeCycle>("Fade in cycle");
}

Effect effectFadeSingleLed() {
  return makeEffect<SingleLedFade>("Fade single led", 255);
}

Effect effectRandomSplashes() {
  return makeEffect<RandomAsynchronousSplashes>("Random splashes");
}

Effect effectRandomCompensatedSplashes() {
  return makeEffect<RandomSplashesCompensated>("Random compensated splashes");
}

Effect effectRandomBlinks() {
  return makeEffect<RandomAsynchronousSplashes>(
    "Random blinks", 
    std::vector<RandomSplashes::BrightnessSettings>({{0, 0}, {255, 255}}));
}

Effect effectAsycFire() {
  return makeEffect<RandomAsynchronousSplashes>(
    "Async fire", std::vector<RandomSplashes::BrightnessSettings>({{51, 255}}));
}

Effect effectAsycFlame() {
  return makeEffect<RandomAsynchronousSplashes>(
    "Async flame", 
    std::vector<RandomSplashes::BrightnessSettings>({{25, 255}, {51, 255}, {76, 255}, {102, 255}, {127, 255}, {51, 255}, {153, 255}, {178, 255}, {204, 255}}), 
    10);
}

Effect effectSyncFire() {
  return makeEffect<RandomSynchronousSplashes>(
    "Sync fire", std::vector<RandomSplashes::BrightnessSettings>({{51, 255}}));
}

Effect effectSyncFlame() {
  return makeEffect<RandomSynchronousSplashes>(
    "Sync flame", 
    std::vector<RandomSplashes::BrightnessSettings>({{25, 255}, {51, 255}, {76, 255}, {102, 255}, {127, 255}, {51, 255}, {153, 255}, {178, 255}, {204, 255}}),
    10);
}

std::vector<Effect> allEffects() {
  return std::vector<Effect>({
    noAnimation(),
    effectRandomCompensatedSplashes(),
    effectFadeOnSwitch(),
    effectFadeSingleLed(),
    effectFadeInCycle(),
    effectRandomSplashes(),
    effectRandomBlinks(),
    effectAsycFire(),
    effectAsycFlame(),
    effectSyncFire(),
    effectSyncFlame(),
  });
}

std::vector<Effect> defaultEffects() {
  return std::vector<Effect>({
    effectRandomCompensatedSplashes(),
    effectFadeOnSwitch(),
    effectFadeSingleLed(),
  });
}

#define EFFECT_LIST (allEffects())