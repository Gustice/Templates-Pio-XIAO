#pragma once

#include <Arduino.h>

class Button {
  public:
    enum eEvents {
        BTN_IDLE,
        BTN_PRESSED,
        BTN_HOLDING,
        BTN_RELEASED,
    };

    eEvents poll();
    Button(int pin);

  private:
    const int _pin;
    uint16_t _oldState = 0;
    uint16_t _holdSteps = 0;
};