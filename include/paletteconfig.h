#ifndef PALETTECONFIG_H
#define PALETTECONFIG_H

#include <FastLED.h>
#include "palettemode.h"

enum PaletteType {
    RAINBOW,
    RAINBOW_STRIPE,
    PARTY,
    OCEAN,
    LAVA,
    FOREST,
    CUSTOM
};

struct PaletteConfig {
    CRGBPalette16 palette;
    PaletteType type;
    PaletteMode mode;
    uint16_t delay;
    uint8_t stretch;
    TBlendType blending;
};

#endif
