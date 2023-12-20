#ifndef CUSTOMPALETTECOMMAND_H
#define CUSTOMPALETTECOMMAND_H

#include "commands/command.h"

class CustomPaletteCommand : public Command {
public:
    void run(char** command, LEDController* controller);
    static CRGB colors[16];
};

#endif
