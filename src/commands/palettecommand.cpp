#include "commands/palettecommand.h"
#include "paletteparser.h"
#include "paletteconfig.h"
#include "palettemode.h"

PaletteCommand::PaletteCommand(LEDController& controller): Command(controller) {}

void PaletteCommand::fire(uint8_t* argArray) {
    const uint8_t rawPalette = argArray[0];

    CRGBPalette16 palette = PaletteParser::parseToPalette(rawPalette);
    _controller.setPalette(palette);
    _controller.setMode(LEDController::Mode::PALETTE);
}

uint8_t PaletteCommand::requiredArgs() {
    return 1;
}
