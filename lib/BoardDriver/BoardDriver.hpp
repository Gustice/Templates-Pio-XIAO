#pragma once

#include "Button.hpp"
#include "Sound.hpp"
#include "U8x8lib.h" // Note this depends on package olikraus/U8g2
#include <Arduino.h>

static constexpr Sound::Tone startJingle[]{
    {Sound::NOTE_C4, 250},
    {Sound::NOTE_E4, 250},
    {Sound::NOTE_PAUSE, 0},
};
static constexpr Sound::Tone btnPressedSound{Sound::NOTE_E3, 125};
static constexpr Sound::Tone btnReleasedSound{Sound::NOTE_C3, 125};

class Board {
  private:
    static constexpr int ButtonPin = 1;

  public:
    U8X8_SSD1306_128X64_NONAME_HW_I2C display;
    Sound buzzer;
    Button button;

    Board(/* args */) : display(U8X8_PIN_NONE), buzzer(A3), button(ButtonPin) {};

    void begin() {
        display.begin();
        display.setFlipMode(0);
        display.setFont(u8x8_font_chroma48medium8_r);
    }
};
