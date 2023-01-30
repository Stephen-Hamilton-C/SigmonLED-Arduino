#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>
#include <ledcontroller.h>

class Command {
public:
    Command(LEDController& controller);
    virtual void fire(uint8_t* argArray) = 0;
    virtual uint8_t requiredArgs() = 0;

protected:
    LEDController& _controller;
};

#endif
