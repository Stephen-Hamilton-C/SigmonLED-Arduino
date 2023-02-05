#include "commands/custompalettecommand.h"
#include "paletteparser.h"

CustomPaletteCommand::CustomPaletteCommand(LEDController& controller): Command(controller) {}

void CustomPaletteCommand::fire(uint8_t *argArray) {
    CRGB colors[16];
    for(uint8_t i = 0; i < 16; i++) {
        colors[i] = CRGB(argArray[i*3+1], argArray[i*3+2], argArray[i*3+3]);
    }

    PaletteParser::customPalette = CRGBPalette16(colors);
    _controller.setPalette(PaletteParser::customPalette);
    _controller.setMode(LEDController::Mode::PALETTE);
}

uint8_t CustomPaletteCommand::requiredArgs() {
    return 48;
}
