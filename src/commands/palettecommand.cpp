#include "commands/palettecommand.h"

#include "util.h"

void PaletteCommand::run(char** command, LEDController& controller) {
    uint8_t paletteType = Util::parseASCIINumber(command[1]);
    CRGBPalette16 palette;
    switch(paletteType) {
        case PaletteType::RAINBOW:
            palette = RainbowColors_p;
            break;
        case PaletteType::RAINBOW_STRIPE:
            palette = RainbowStripeColors_p;
            break;
        case PaletteType::PARTY:
            palette = PartyColors_p;
            break;
        case PaletteType::OCEAN:
            palette = OceanColors_p;
            break;
        case PaletteType::LAVA:
            palette = LavaColors_p;
            break;
        case PaletteType::FOREST:
            palette = ForestColors_p;
            break;
        default:
            paletteType = PaletteType::CUSTOM;
            palette = controller.customPalette;
            break;
    }
    controller.setPalette(palette, (PaletteType)paletteType);
    controller.setMode(LEDController::Mode::PALETTE);
}
