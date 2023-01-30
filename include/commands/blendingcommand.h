#ifndef BLENDINGCOMMAND_H
#define BLENDINGCOMMAND_H

#include "command.h"

class BlendingCommand: public Command {
public:
    BlendingCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
