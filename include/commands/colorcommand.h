#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H

#include "command.h"

class ColorCommand : public Command {
public:
    void run(char** arguments, LEDController& controller);
    void getName(char out[NAME_LEN]);
    int getArgCount();
};

#endif
