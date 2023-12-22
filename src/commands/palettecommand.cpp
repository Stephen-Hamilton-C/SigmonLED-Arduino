#include "commands/palettecommand.h"

#include "util.h"

void PaletteCommand::run(char** command, LEDController* controller) {
    uint8_t paletteType = Util::parseASCIINumber(command[1]);
    
    controller->setPalette((PaletteType)paletteType);
    controller->setMode(LEDController::Mode::PALETTE);
}
