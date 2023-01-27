#ifndef PALETTECOMMAND_H
#define PALETTECOMMAND_H

#include "command.h"

class PaletteCommand: public Command {
public:
    PaletteCommand(LEDController* controller);
    //Override
    void receivedInput(const uint8_t* input[], const uint8_t& len);
};

#endif
