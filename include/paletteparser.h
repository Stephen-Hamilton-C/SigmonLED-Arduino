#ifndef PALETTEPARSER_H
#define PALETTEPARSER_H

#include <stdint.h>
#include <FastLED.h>

namespace PaletteParser {
    CRGBPalette16 parseToPalette(const uint8_t& desiredPalette);
}

#endif
