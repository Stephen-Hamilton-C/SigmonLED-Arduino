#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdint.h>
#include "command.h"
#include "ledcontroller.h"

#define BUFFER_SIZE 64

class InputHandler {
public:
    InputHandler(LEDController& controller);
    void nextByte(const uint8_t desiredCmd);

private:
    LEDController& _controller;
    uint8_t _buffer[BUFFER_SIZE] = {};
    uint8_t _bufferLen = 0;
    Command* _nextCommand = nullptr;

    void fireCommandForArgs();
    void reset();
};

#endif
