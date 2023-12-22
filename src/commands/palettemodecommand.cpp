#include "commands/palettemodecommand.h"

#include "util.h"

void PaletteModeCommand::run(char** command, LEDController* controller) {
    uint8_t paletteMode = Util::parseASCIINumber(command[1]);
    if(paletteMode > 2) {
        paletteMode = PaletteMode::SCROLLING;
    }
    controller->setPaletteMode((PaletteMode)paletteMode);
    controller->setMode(LEDController::Mode::PALETTE);
}
