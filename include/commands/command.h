#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>
#include <ledcontroller.h>

class Command {
public:
    Command(LEDController* controller);
    virtual void receivedInput(const uint8_t* input[], const uint8_t& len) = 0;

protected:
    LEDController* _controller;
};

#endif
