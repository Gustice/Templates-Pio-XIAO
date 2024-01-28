/**
 * @file StatusLed.h
 * @author Gustice
 * @brief Simple Status-LED-driver
 *
 * @copyright Copyright (c) 2023
 */
#pragma once

#include <Arduino.h>

/**
 * @brief Status-LED-driver
 * @details Display of basic patterns like steady-on or blinking.
 * @note Needs constant tick, so it can maintain state of given output.
 */
class StatusLed {
  public:
    /// @brief Display Mode
    enum Mode : uint8_t {
        Off = 0,     ///< steady off
        SteadyOn,    ///< steady on
        Blinking,    ///< constant blinking
        Flash,       ///< short flash with following pause
        DoubleFlash, ///< short flashes with following pause
        Burst,       ///< burst with following pause
        Flicker,     ///< constant burst
        Modes        ///< Number of modes
    };

    /// @brief Led-Logic of actual connected LED
    enum LedLogic {
        // High driven LED
        Normal,
        // Low-driven LED
        Inverted
    };

    /// @brief Constructor
    /// @param port Port instance
    /// @param logic Logic of connected LED
    /// @param mode Optional start mode
    StatusLed(int port, LedLogic logic = LedLogic::Normal, Mode mode = Mode::Off)
        : _port(port), _logic(logic), _rotatingIdx(0) {
        pinMode(port, OUTPUT);
        Set(mode);
    };

    /// @brief Set mode
    void Set(Mode mode) {
        _mode = mode;
        _state = States[(int)_mode];

        if (_logic == LedLogic::Inverted) {
            _state = ~_state;
        }
    }

    /// @brief Trigger next step, output will be automatically updated
    void Tick();

  private:
    static constexpr int MaxIdxCount = 15;
    const int _port;
    const LedLogic _logic;

    Mode _mode;
    int _rotatingIdx;
    static const uint16_t States[Modes];
    uint16_t _state;
};
