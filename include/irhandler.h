#ifndef IRHANDLER_H
#define IRHANDLER_H

#include "ledcontroller.h"
#include "paralleltimer.h"

#define VALUETYPE_MAX 2
#define PALETTETYPE_MAX 5

class IRHandler {
public:
    IRHandler(LEDController* ledController);
    void loop();
    bool isIdle();

private:
    enum ValueType {
        BRIGHTNESS,
        PALETTE_TYPE,
    };

    uint32_t _lastInput = 0;
    uint64_t _lastDataTimestamp = 0;

    void printInput(const uint32_t input);
    void handleInput(const uint32_t input);
    void handleDigit(const uint8_t digit);
    void handleValueIncrement(const int8_t direction);
    void handleSwitchValueType(const int8_t direction);
    void handleSwitchMode();
    // TODO: Read the paper, what did IRIN_COLOR do? Need better name
    void handleColor();

    LEDController* _controller;
    uint8_t _incrementMagnitude = 5;
    ValueType _currentType = ValueType::BRIGHTNESS;
};

#endif
