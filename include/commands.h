#ifndef COMMANDS_H
#define COMMANDS_H

#include <string.h>
#include "commandinfo.h"
#include "util.h"

#include "commands/blendingcommand.h"
#include "commands/brightnesscommand.h"
#include "commands/colorcommand.h"
#include "commands/custompalettecommand.h"
#include "commands/delaycommand.h"
#include "commands/hellocommand.h"
#include "commands/palettecommand.h"
#include "commands/palettemodecommand.h"
#include "commands/stretchcommand.h"

struct Commands {
public:
    static CommandInfo getArgCount(char command[]) {
        if(Util::strStartsWith(command, "color")) {
            return CommandInfo {
                argCount: 4,
                command: new ColorCommand()
            };
        }
        if(Util::strStartsWith(command, "hello")) {
            return CommandInfo {
                argCount: 1,
                command: new HelloCommand()
            };
        }
        if(Util::strStartsWith(command, "blend")) {
            return CommandInfo {
                argCount: 2,
                command: new BlendingCommand()
            };
        }
        if(Util::strStartsWith(command, "bright")) {
            return CommandInfo {
                argCount: 2,
                command: new BrightnessCommand()
            };
        }
        if(Util::strStartsWith(command, "delay")) {
            return CommandInfo {
                argCount: 2,
                command: new DelayCommand()
            };
        }
        if(Util::strStartsWith(command, "palette")) {
            return CommandInfo {
                argCount: 2,
                command: new PaletteCommand()
            };
        }
        if(Util::strStartsWith(command, "pmode")) {
            return CommandInfo {
                argCount: 2,
                command: new PaletteModeCommand()
            };
        }
        if(Util::strStartsWith(command, "stretch")) {
            return CommandInfo {
                argCount: 2,
                command: new StretchCommand()
            };
        }
        if(Util::strStartsWith(command, "custom")) {
            return CommandInfo {
                argCount: 49,
                command: new CustomPaletteCommand()
            };
        }

        return CommandInfo {
            argCount: -1,
            command: nullptr
        };
    }
};

#endif
