#ifndef COMMAND_H
#define COMMAND_H

#include "ledcontroller.h"

class Command {
public:
    virtual void run(char** command, LEDController* controller) = 0;
};

#endif
