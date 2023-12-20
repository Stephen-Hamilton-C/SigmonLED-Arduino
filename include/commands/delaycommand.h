#ifndef DELAYCOMMAND_H
#define DELAYCOMMAND_H

#include "commands/command.h"

class DelayCommand : public Command {
public:
    void run(char** command, LEDController* controller);
};

#endif
