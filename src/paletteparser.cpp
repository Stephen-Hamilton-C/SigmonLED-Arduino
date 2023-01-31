#include "paletteparser.h"

CRGBPalette16 PaletteParser::customPalette = CRGBPalette16(CRGB(0, 0, 0));

CRGBPalette16 PaletteParser::parseToPalette(const uint8_t& desiredPalette) {
    switch(desiredPalette) {
        case 'r': return RainbowColors_p;
        case 'R': return RainbowStripeColors_p;
        case 'c': return CloudColors_p;
        case 'p': return PartyColors_p;
        case 'o': return OceanColors_p;
        case 'l': return LavaColors_p;
        case 'f': return ForestColors_p;
        case 'C': return customPalette;
        default: return CRGBPalette16(CRGB(0, 0, 0));
    }
}
