#ifndef BRIGHTNESSCOMMAND_H
#define BRIGHTNESSCOMMAND_H

#include "commands/command.h"

class BrightnessCommand : public Command {
public:
    void run(char** command, LEDController* controller);
};

#endif
