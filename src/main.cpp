#include "main.hpp"

const int BlinkTime = 50;

static StatusLed _statusLed(LED_BUILTIN, StatusLed::LedLogic::Inverted);
static RotatingIndex<int> _tickIdx(16);
static RotatingIndex<int> _timeTick(1000 / BlinkTime);

#ifdef EXTENSION_BOARD
Board board;
#endif

void setup() {
    Serial.begin(9600);
    _statusLed.Set(StatusLed::Mode::DoubleFlash);

#ifdef EXTENSION_BOARD
    board.begin();
    board.display.setCursor(0, 0);
    board.display.print("Internal Demo:");
    board.display.setCursor(0, 1);
    board.display.setCursor(0, 2);
    board.display.print("Btn=");
    board.buzzer.play(startJingle);

    board.display.setCursor(0, 3);
    board.display.print(board.time.getDateStringNow().c_str());
    board.display.setCursor(0, 4);
    board.display.print(board.time.getTimeStringNow().c_str());
#endif
}

void loop() {
    if (_tickIdx.IncrementAndCheckIfRevolves()) {
        Serial.println("");
        Serial.print("Tick ");
    }
    Serial.print(".");

#ifdef EXTENSION_BOARD
    board.display.clearLine(1);
    board.display.setCursor(_tickIdx.GetIndex(), 1);
    board.display.print(".");

    board.display.setCursor(4, 2);
    board.display.print(board.button.readRaw());
    auto btn = board.button.read();
    if (btn == Button::BTN_PRESSED) {
        board.buzzer.play(btnPressedSound);
    } else if (btn == Button::BTN_RELEASED) {
        board.buzzer.play(btnReleasedSound);
    }

    if (_timeTick.IncrementAndCheckIfRevolves()) {
        board.display.setCursor(0, 4);
        board.display.print(board.time.getTimeStringNow().c_str());
    }
#endif

    _statusLed.Tick();
    delay(BlinkTime);
}
