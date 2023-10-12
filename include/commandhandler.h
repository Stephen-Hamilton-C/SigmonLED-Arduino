#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "ledcontroller.h"

#include "commands/command.h"
#include "commands/colorcommand.h"

#define COMMAND_COUNT 1

class CommandHandler {
public:
    void loop();
    void execute(char** arguments, int argCount);
    int getArgCount(char cmdName[]);

private:
    LEDController _controller;
    Command* _commands[COMMAND_COUNT] = {new ColorCommand()};
};

#endif
