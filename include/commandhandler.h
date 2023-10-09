#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "ledcontroller.h"

class CommandHandler {
public:
    void loop();
    void execute(char** arguments, int argCount);

private:
    LEDController _controller;
};

#endif
