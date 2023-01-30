#include "commands/palettemodecommand.h"

PaletteModeCommand::PaletteModeCommand(LEDController &controller): Command(controller) {}

void PaletteModeCommand::fire(uint8_t* argArray) {
    const uint8_t rawPaletteMode = argArray[0];

    PaletteMode paletteMode = (PaletteMode) rawPaletteMode;
    _controller.setPaletteMode(paletteMode);
    _controller.setMode(LEDController::Mode::PALETTE);
}

uint8_t PaletteModeCommand::requiredArgs() {
    return 1;
}
