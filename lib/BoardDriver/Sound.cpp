#include "Sound.hpp"

#include <Arduino.h>
constexpr int pause = 25;

void Sound::play(const Tone * melody) {
    const Tone *note = melody;
    while (note->duration > 0) {
        play(*note);
        note++;
    }
}

void Sound::play(const Tone & note) {
    tone(_speakerPin, note.note, note.duration - pause);
    delay(note.duration);
    noTone(_speakerPin);
}
