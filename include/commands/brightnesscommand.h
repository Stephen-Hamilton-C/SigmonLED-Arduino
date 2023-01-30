#ifndef BRIGHTNESSCOMMAND_H
#define BRIGHTNESSCOMMAND_H

#include "command.h"

class BrightnessCommand: public Command {
public:
    BrightnessCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
