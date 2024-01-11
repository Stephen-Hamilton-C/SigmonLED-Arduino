#include "config.h"
#if ENABLE_IR_INPUT

#ifndef IRHANDLER_H
#define IRHANDLER_H

#include "ledcontroller.h"
#include "paralleltimer.h"

#define VALUETYPE_MAX 4
#define PALETTETYPE_MAX 6
#define PALETTEMODE_MAX 2
#define EDITOR_GLOW_TICKS 10000
#define EDITOR_OFF_FLASH 100
#define EDITOR_ON_FLASH 800

class IRHandler {
public:
    IRHandler(LEDController* ledController);
    void loop();
    bool isIdle();

private:
    enum ValueType {
        BRIGHTNESS,
        PALETTE_TYPE,
        DELAY,
        STRETCH,
        PALETTE_MODE,
    };
    enum EditorState {
        HUE,
        SATURATION,
    };

    uint32_t _lastInput = 0;
    bool _lastInputRepeat = false;
    uint64_t _lastDataTimestamp = 0;

    void printInput(const uint32_t input);
    void handleInput();
    void handleDecode();
    void handleDigit(const uint8_t digit);
    void handleValueIncrement(const int8_t direction);
    void handleSwitchValueType(const int8_t direction);
    void handleSelect();
    void handleModeSwitch();

    void editStart();
    void editHue();
    void editSaturation();
    void editEnd();


    LEDController* _controller;
    ValueType _currentType = ValueType::BRIGHTNESS;
    bool _blinking = false;
    CRGB _colors[10] = {
        CRGB::White,
        CRGB(255, 200, 100),
        CRGB::Red,
        CRGB::Orange,
        CRGB::Yellow,
        CRGB::Green,
        CRGB::Teal,
        CRGB::Blue,
        CRGB::Purple,
        CRGB::Magenta
    };
    uint8_t _currentColor = 0;

    bool _colorEditor = false;
    int8_t _colorDirection = -1;
    uint64_t _editorTick = 0;
    uint8_t _brightness = 0;
    EditorState _editorState = EditorState::HUE;
    uint8_t _colorHue = 0;
    uint8_t _colorSat = 255;
};

#endif
#endif
