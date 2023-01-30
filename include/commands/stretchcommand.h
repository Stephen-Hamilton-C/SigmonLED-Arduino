#ifndef STRETCHCOMMAND_H
#define STRETCHCOMMAND_H

#include "command.h"

class StretchCommand: public Command {
public:
    StretchCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
