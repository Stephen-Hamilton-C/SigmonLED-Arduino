#ifndef PALETTECOMMAND_H
#define PALETTECOMMAND_H

#include "commands/command.h"

class PaletteCommand : public Command {
public:
    void run(char** command, LEDController& controller);
};

#endif
