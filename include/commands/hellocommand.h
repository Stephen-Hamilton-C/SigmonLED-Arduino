#ifndef HELLOCOMMAND_H
#define HELLOCOMMAND_H

#include "commands/command.h"

class HelloCommand : public Command {
public:
    void run(char** command, LEDController& controller);
};

#endif
