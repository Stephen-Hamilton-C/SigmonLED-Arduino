#ifndef BLENDINGCOMMAND_H
#define BLENDINGCOMMAND_H

#include "commands/command.h"

class BlendingCommand : public Command {
public:
    void run(char** command, LEDController& controller);
};

#endif
