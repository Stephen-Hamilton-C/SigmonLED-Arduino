#ifndef DELAYCOMMAND_H
#define DELAYCOMMAND_H

#include "command.h"

class DelayCommand: public Command {
public:
    DelayCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
