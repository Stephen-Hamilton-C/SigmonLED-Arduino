#ifndef PALETTEMODECOMMAND_H
#define PALETTEMODECOMMAND_H

#include "command.h"

class PaletteModeCommand : public Command {
public:
    PaletteModeCommand(LEDController& controller);
    // Override
    void fire(uint8_t* argArray);
    uint8_t requiredArgs();
};

#endif
