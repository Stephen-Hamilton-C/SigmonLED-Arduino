#ifndef COMMANDS_H
#define COMMANDS_H

#include <string.h>
#include "commandinfo.h"

#include "commands/testcommand.h"

struct Commands {
public:
    static CommandInfo getArgCount(char command[]) {
        if(strstr(command, "test") != NULL) {
            return CommandInfo {
                argCount: 1,
                command: new TestCommand()
            };
        }

        return CommandInfo {
            argCount: -1,
            command: nullptr
        };
    }
};

#endif
