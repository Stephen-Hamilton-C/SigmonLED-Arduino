#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H

#include "command.h"

class ColorCommand: public Command {
public:
    ColorCommand(LEDController* controller);

    //Override
    void receivedInput(const uint8_t* input[], const uint8_t& len);
};

#endif
