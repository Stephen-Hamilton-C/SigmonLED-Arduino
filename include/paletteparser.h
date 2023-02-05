#ifndef PALETTEPARSER_H
#define PALETTEPARSER_H

#include <stdint.h>
#include <FastLED.h>

class PaletteParser {
public:
    static CRGBPalette16 parseToPalette(const uint8_t& desiredPalette);
    static CRGBPalette16 customPalette;
};

#endif
