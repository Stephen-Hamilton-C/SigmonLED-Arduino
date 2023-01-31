#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdint.h>
#include "command.h"
#include "ledcontroller.h"

#define BUFFER_SIZE 256
#define BUFFER_TIMEOUT 1000

class InputHandler {
public:
    InputHandler(LEDController& controller);
    void processByte(const uint8_t byte);
    void loop();

private:
    LEDController& _controller;
    uint8_t _buffer[BUFFER_SIZE] = {};
    uint8_t _bufferLen = 0;
    unsigned long _timeOfLastByte = 0;

    Command* getCommand(const uint8_t& cmdByte);
};

#endif
