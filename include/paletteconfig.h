#ifndef PALETTECONFIG_H
#define PALETTECONFIG_H

#include <FastLED.h>
#include "palettemode.h"

struct PaletteConfig {
    CRGBPalette16 palette;
    PaletteMode mode;
    uint16_t delay;
    uint8_t stretch;
    TBlendType blending;
};

#endif
