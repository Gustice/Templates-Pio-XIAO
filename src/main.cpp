#include "main.hpp"

const int BlinkTime = 50 ;

static StatusLed _statusLed(LED_BUILTIN, StatusLed::LedLogic::Inverted);

void setup() {
    Serial.begin(9600);
    _statusLed.Set(StatusLed::Mode::DoubleFlash);
}

static RotatingIndex<int> _tickIdx(16);

void loop() {
    if (_tickIdx.IncrementAndCheckIfRevolves()) {
        Serial.println("");
        Serial.print("Tick ");
    }
    Serial.print(".");

    _statusLed.Tick();
    delay(BlinkTime); 
}
