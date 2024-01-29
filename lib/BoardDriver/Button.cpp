
#include "Button.hpp"

Button::Button(int pin) : _pin(pin) {
    pinMode(_pin, INPUT_PULLUP);
    uint32_t state = digitalRead(_pin);
    _oldState = state;
}

Button::eEvents Button::poll() {
    uint32_t state = digitalRead(_pin);
    uint32_t states = ((_oldState & 1) << 1) | (state & 1);
    _oldState = state;

    switch (states) {

    default: // Idle
    case 0x00:
        return BTN_IDLE;

    case 0x01: // Press-Event
        return BTN_PRESSED;

    case 0x03: // Hold
        _holdSteps++;
        return BTN_HOLDING;

    case 0x02: // Release-Event
        _holdSteps = 0;
        return BTN_RELEASED;
    }
}