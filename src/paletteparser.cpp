#include "paletteparser.h"

CRGBPalette16 PaletteParser::_customPalette = CRGBPalette16(CRGB(0, 0, 0));

CRGBPalette16 PaletteParser::parseToPalette(const uint8_t& desiredPalette) {
    switch(desiredPalette) {
        case 'r':
            Serial.println("Received Rainbow palette");
            return RainbowColors_p;
        case 'R':
            Serial.println("Received Rainbow Stripe palette");
            return RainbowStripeColors_p;
        case 'c':
            Serial.println("Received Cloud palette");
            return CloudColors_p;
        case 'p':
            Serial.println("Received Party palette");
            return PartyColors_p;
        case 'o':
            Serial.println("Received Ocean palette");
            return OceanColors_p;
        case 'l':
            Serial.println("Received Lava palette");
            return LavaColors_p;
        case 'f':
            Serial.println("Received Forest palette");
            return ForestColors_p;
        case 'C':
            Serial.println("Received Custom palette");
            return _customPalette;
        default:
            Serial.println("Received unknown palette");
            return CRGBPalette16(CRGB(0, 0, 0));
    }
}
