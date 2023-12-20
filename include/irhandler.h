#ifndef IRHANDLER_H
#define IRHANDLER_H

#include "ledcontroller.h"
#include "paralleltimer.h"

class IRHandler {
public:
    IRHandler(LEDController* ledController);
    void loop();

    bool isIdle();

private:
    uint32_t _lastInput = 0;
    uint64_t _lastDataTimestamp = 0;

    void printInput(const uint32_t input);
    void handleInput(const uint32_t input);
    void off();

    LEDController* _controller;
};

#endif
