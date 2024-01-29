#include "main.hpp"

#ifdef EXTENSION_BOARD
#include "Button.hpp"
#include "Sound.hpp"
#endif

const int BlinkTime = 50;

static StatusLed _statusLed(LED_BUILTIN, StatusLed::LedLogic::Inverted);
static RotatingIndex<int> _tickIdx(16);

#ifdef EXTENSION_BOARD
U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);
Sound buzzer(A3);
constexpr int ButtonPin = 1;
Button button(ButtonPin);

Sound::Tone startJingle[]{
    {Sound::NOTE_C4, 250},
    {Sound::NOTE_E4, 250},
    {Sound::NOTE_PAUSE, 0},
};
Sound::Tone btnPressedSound{Sound::NOTE_E3, 125};
Sound::Tone btnReleasedSound{Sound::NOTE_C3, 125};
#endif


void setup() {
    Serial.begin(9600);
    _statusLed.Set(StatusLed::Mode::DoubleFlash);

#ifdef EXTENSION_BOARD
    display.begin();
    display.setFlipMode(0);
    display.setFont(u8x8_font_chroma48medium8_r);

    display.setCursor(0, 0);
    display.print("Internal Demo:");
    display.setCursor(0, 1);
    display.setCursor(0, 2);
    display.print("Btn=");
    buzzer.play(startJingle);
#endif
}

void loop() {
    if (_tickIdx.IncrementAndCheckIfRevolves()) {
        Serial.println("");
        Serial.print("Tick ");
    }
    Serial.print(".");

#ifdef EXTENSION_BOARD
    display.clearLine(1);
    display.setCursor(_tickIdx.GetIndex(), 1);
    display.print(".");

    display.setCursor(4, 2);
    display.print(digitalRead(ButtonPin));
    auto btn = button.poll();
    if (btn == Button::BTN_PRESSED) {
        buzzer.play(btnPressedSound);
    } else if (btn == Button::BTN_RELEASED) {
        buzzer.play(btnReleasedSound);
    }
#endif

    _statusLed.Tick();
    delay(BlinkTime);
}
