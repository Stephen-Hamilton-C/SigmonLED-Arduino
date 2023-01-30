#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H

#include "command.h"

class ColorCommand: public Command {
public:
    ColorCommand(LEDController& controller);

    //Override
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
