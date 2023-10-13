#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

class TestCommand : public Command {
public:
    void run(char** command, LEDController& controller);
};

#endif
