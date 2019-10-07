#include <Arduino.h>
#include <unity.h>

#include <helpers.h>

void test_safeNameBuilder(void) {
  TEST_ASSERT_EQUAL_STRING("123", makeSafeName("123"));
  TEST_ASSERT_EQUAL_STRING("cointreau_bottle_2", makeSafeName("Cointreau Bottle 2"));
  TEST_ASSERT_EQUAL_STRING("inthemiddle", makeSafeName(" -=InTheMiddle=- "));
}

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_safeNameBuilder);
  UNITY_END();
}

void loop() {
}
