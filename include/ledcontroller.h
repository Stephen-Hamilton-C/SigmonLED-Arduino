#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <FastLED.h>
#include "config.h"
#include "palettemode.h"
#include "paletteconfig.h"

class LEDController {
public:
    enum Mode {
        COLOR,
        PALETTE,
    };

    bool updateQueued = false;

    LEDController();
    void loop();
    void paletteLoop();

    const Mode getMode();
    void setMode(const Mode& mode);
    const CRGB getColor();
    void setColor(const CRGB& color);
    const uint8_t getBrightness();
    void setBrightness(const uint8_t& brightness);

    void setPalette(const CRGBPalette16& palette, const PaletteType& type);
    void setPaletteMode(const PaletteMode& mode);
    void setPaletteDelay(const uint16_t& delay);
    void setPaletteStretch(const uint8_t& stretch);
    void setPaletteBlending(const bool& blending);

    void setGradient(const CRGB& start, const CRGB& end);
    void distributePalette(const CRGBPalette16& palette);

    const PaletteConfig& getPaletteConfig();

    CRGBPalette16 customPalette = CRGBPalette16(CRGB::Black);
private:
    CRGB _leds[LED_COUNT];

    Mode _currentMode = Mode::COLOR;
    CRGB _currentColor = CRGB(255, 255, 255);
    uint8_t _scrollingColorIndex = 0;
    uint8_t _brightness = 255;
    unsigned long _lastUpdate = 0;

    PaletteConfig _paletteConfig = PaletteConfig { 
        palette: RainbowColors_p,
        type: PaletteType::RAINBOW,
        mode: PaletteMode::SCROLLING,
        delay: 10,
        stretch: 3,
        blending: TBlendType::LINEARBLEND,
    };

    void setPaletteStaticColor();
    uint8_t calculateGradientPixel(const int i, const uint8_t final, const uint8_t initial);
    void updateStrip();
};

#endif
