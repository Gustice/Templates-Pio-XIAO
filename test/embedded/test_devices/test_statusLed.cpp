#include "StatusLed.h"
#include <Arduino.h>
#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

int LED_PIN = LED_BUILTIN;

void test_LedStaysDark(void) {
    StatusLed dut(LED_PIN);

    for (size_t i = 0; i < 30; i++) {
        dut.Tick();
        TEST_ASSERT_EQUAL(LOW, digitalRead(LED_PIN));
        delay(10);
    }
}

void test_LedIsConstantOn(void) {
    StatusLed dut(LED_PIN);

    dut.Set(StatusLed::Mode::SteadyOn);
    for (size_t i = 0; i < 30; i++) {
        dut.Tick();
        TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_PIN));
        delay(10);
    }
}

void test_LedBlinks(void) {
    StatusLed dut(LED_PIN);

    dut.Set(StatusLed::Mode::Blinking);
    for (size_t n = 0; n < 2; n++) {
        for (size_t i = 0; i < 8; i++) {
            dut.Tick();
            TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_PIN));
            delay(20);
        }
        for (size_t i = 0; i < 8; i++) {
            dut.Tick();
            TEST_ASSERT_EQUAL(LOW, digitalRead(LED_PIN));
            delay(20);
        }
    }
}

void test_LedBlinks_InverseLogic(void) {
    StatusLed dut(LED_PIN, StatusLed::LedLogic::Inverted);

    dut.Set(StatusLed::Mode::Blinking);
    for (size_t n = 0; n < 2; n++) {
        for (size_t i = 0; i < 8; i++) {
            dut.Tick();
            TEST_ASSERT_EQUAL(LOW, digitalRead(LED_PIN));
            delay(20);
        }
        for (size_t i = 0; i < 8; i++) {
            dut.Tick();
            TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_PIN));
            delay(20);
        }
    }
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_LedStaysDark);
    RUN_TEST(test_LedIsConstantOn);
    RUN_TEST(test_LedBlinks);
    RUN_TEST(test_LedBlinks_InverseLogic);
    UNITY_END(); // stop unit testing
}

void loop() {
    delay(500);
}