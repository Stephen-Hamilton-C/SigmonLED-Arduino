#include "commands/stretchcommand.h"

#include "util.h"

void StretchCommand::run(char** command, LEDController* controller) {
    uint8_t stretch = Util::parseASCIINumber(command[1]);
    controller->setPaletteStretch(stretch);
    controller->setMode(LEDController::Mode::PALETTE);
}
