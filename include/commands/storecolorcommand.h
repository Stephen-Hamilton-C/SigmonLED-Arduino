#ifndef STORECOLORCOMMAND_H
#define STORECOLORCOMMAND_H

#include "command.h"

class StoreColorCommand: public Command {
public:
    StoreColorCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
