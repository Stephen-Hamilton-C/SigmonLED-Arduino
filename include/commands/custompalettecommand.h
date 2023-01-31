#ifndef CUSTOMPALETTECOMMAND_H
#define CUSTOMPALETTECOMMAND_H

#include "command.h"

class CustomPaletteCommand: public Command {
public:
    CustomPaletteCommand(LEDController& controller);
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
