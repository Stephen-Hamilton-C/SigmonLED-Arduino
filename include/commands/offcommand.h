#ifndef OFFCOMMAND_H
#define OFFCOMMAND_H

#include "command.h"

class OffCommand: public Command {
public:
    OffCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
