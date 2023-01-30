#ifndef PALETTECOMMAND_H
#define PALETTECOMMAND_H

#include "command.h"

class PaletteCommand: public Command {
public:
    PaletteCommand(LEDController& controller);
    //Override
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
