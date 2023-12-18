#ifndef COMMANDINFO_H
#define COMMANDINFO_H

#include "commands/command.h"

struct CommandInfo {
    int argCount;
    Command* command;
};

#endif
