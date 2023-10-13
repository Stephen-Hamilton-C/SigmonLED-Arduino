#include "commands/custompalettecommand.h"

#include "util.h"

void CustomPaletteCommand::run(char** command, LEDController& controller) {
    // custom 255 255 255 127 127 127 0 0 0
    CRGB colors[16];
    for(int i = 0; i < 16; i++) {
        uint8_t r = Util::parseASCIINumber(command[i*3 + 1]);
        uint8_t g = Util::parseASCIINumber(command[i*3 + 2]);
        uint8_t b = Util::parseASCIINumber(command[i*3 + 3]);
        colors[i] = CRGB(r, g, b);
    }
    CRGBPalette16 palette = CRGBPalette16(colors);
    controller.customPalette = palette;
    controller.setPalette(palette, PaletteType::CUSTOM);
    controller.setMode(LEDController::Mode::PALETTE);
}
