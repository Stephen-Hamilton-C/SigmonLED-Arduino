#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H

#include "command.h"
#include "constants.h"

class ColorCommand: public Command {
public:
    ColorCommand(LEDController& controller);

    //Override
    void receivedInput(const uint8_t (&input)[READ_BUFFER_SIZE], const uint8_t& len);
};

#endif
