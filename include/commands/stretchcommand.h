#ifndef STRETCHCOMMAND_H
#define STRETCHCOMMAND_H

#include "commands/command.h"

class StretchCommand : public Command {
public:
    void run(char** command, LEDController* controller);
};

#endif
