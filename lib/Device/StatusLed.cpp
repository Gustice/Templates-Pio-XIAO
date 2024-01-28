#include "StatusLed.h"

const uint16_t StatusLed::States[StatusLed::Modes]{
    0x0000, // Off
    0xFFFF, // SteadyOn
    0xFF00, // Blinking
    0xF000, // Flashing
    0x8800, // DoubleFlash
    0xAA00, // Burst
    0xAAAA, // Flicker
};

void StatusLed::Tick() {
    auto s = _rotatingIdx++;
    if (_rotatingIdx > MaxIdxCount)
        _rotatingIdx = 0;

    auto l = _state >> (MaxIdxCount - s) & 1;
        
    digitalWrite(_port, l);
}
