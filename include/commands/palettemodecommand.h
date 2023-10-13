#ifndef PALETTEMODECOMMAND_H
#define PALETTEMODECOMMAND_H

#include "commands/command.h"

class PaletteModeCommand : public Command {
public:
    void run(char** command, LEDController& controller);
};

#endif
