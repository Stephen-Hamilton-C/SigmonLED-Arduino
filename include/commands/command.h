#ifndef COMMAND_H
#define COMMAND_H

#include "ledcontroller.h"

#define NAME_LEN 16

class Command {
public:
    virtual void run(char** arguments, LEDController& controller) = 0;
    virtual void getName(char out[NAME_LEN]) = 0;
    virtual int getArgCount() = 0;
};

#endif
