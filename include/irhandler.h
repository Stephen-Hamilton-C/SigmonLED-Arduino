#ifndef IRHANDLER_H
#define IRHANDLER_H

#include "ledcontroller.h"
#include "paralleltimer.h"

#define VALUETYPE_MAX 3
#define PALETTETYPE_MAX 6

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
    };

    uint32_t _lastInput = 0;
    bool _lastInputRepeat = false;
    uint64_t _lastDataTimestamp = 0;

    void printInput(const uint32_t input);
    void handleInput();
    void handleDigit(const uint8_t digit);
    void handleValueIncrement(const int8_t direction);
    void handleSwitchValueType(const int8_t direction);
    void handleSelect();
    void handleModeSwitch();
    void blink(const uint8_t times, const uint16_t interval);

    LEDController* _controller;
    uint8_t _incrementMagnitude = MAX_INCREMENT / 2;
    ValueType _currentType = ValueType::BRIGHTNESS;
    bool _blinking = false;

};

#endif
