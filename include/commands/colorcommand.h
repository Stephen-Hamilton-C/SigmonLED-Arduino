#ifndef COLORCOMMAND_H
#define COLORCOMMAND_H

#include "commands/command.h"

class ColorCommand : public Command {
public:
    void run(char** command, LEDController* controller);
};

#endif
