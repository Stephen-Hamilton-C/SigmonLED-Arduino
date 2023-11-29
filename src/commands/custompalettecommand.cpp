#include "commands/custompalettecommand.h"

#include "util.h"

CRGB CustomPaletteCommand::colors[16] = {
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black
};


void CustomPaletteCommand::run(char** command, LEDController& controller) {
    // custom 0 255 255 255
    // custom 1 0 0 0
    // ...
    // custom 15 0 0 0

    uint8_t index = Util::parseASCIINumber(command[1]);
    if(index > 15) {
        return;
    }

    uint8_t r = Util::parseASCIINumber(command[2]);
    uint8_t g = Util::parseASCIINumber(command[3]);
    uint8_t b = Util::parseASCIINumber(command[4]);

    CustomPaletteCommand::colors[index] = CRGB(r, g, b);

    CRGBPalette16 palette = CRGBPalette16(CustomPaletteCommand::colors);
    controller.customPalette = palette;
    // controller.setPalette(palette, PaletteType::CUSTOM);
    // controller.setMode(LEDController::Mode::PALETTE);
}
