#ifndef COMMANDS_H
#define COMMANDS_H

#include <string.h>
#include "commandinfo.h"

#include "commands/testcommand.h"
#include "commands/colorcommand.h"

struct Commands {
public:
    static CommandInfo getArgCount(char command[]) {
        if(strstr(command, "test") != NULL) {
            return CommandInfo {
                argCount: 1,
                command: new TestCommand()
            };
        }
        if(strstr(command, "color") != NULL) {
            return CommandInfo {
                argCount: 4,
                command: new ColorCommand()
            };
        }

        return CommandInfo {
            argCount: -1,
            command: nullptr
        };
    }

    static int parseASCIINumber(char string[]) {
        int num = 0;
        int i = 0;
        while(string[i] != '\0') {
            int asciiInt = string[i] - '0';
            if(asciiInt >= 0 && asciiInt <= 9) {
                num *= 10;
                num += asciiInt;
            }

            i++;
        }

        return num;
    }
};

#endif
