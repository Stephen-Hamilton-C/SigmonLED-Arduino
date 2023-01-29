#ifndef PALETTECOMMAND_H
#define PALETTECOMMAND_H

#include "command.h"
#include "constants.h"

class PaletteCommand: public Command {
public:
    PaletteCommand(LEDController& controller);
    //Override
    void receivedInput(const uint8_t (&input)[READ_BUFFER_SIZE], const uint8_t& len);
};

#endif
