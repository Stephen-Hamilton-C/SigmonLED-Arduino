#ifndef ONCOMMAND_H
#define ONCOMMAND_H

#include "command.h"

class OnCommand: public Command {
public:
    OnCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();

    static CRGB storedColor;
};

#endif
