#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <FastLED.h>
#include <SoftwareSerial.h>
#include "config.h"
#include "palettemode.h"
#include "paletteconfig.h"

class LEDController {
public:
    enum Mode {
        COLOR,
        PALETTE,
    };

    LEDController();
    void loop();
    void paletteLoop();

    void setMode(const Mode& mode);
    void setColor(const CRGB& color);
    void setBrightness(const uint8_t& brightness);

    void setPalette(const CRGBPalette16& palette);
    void setPaletteMode(const PaletteMode& mode);
    void setPaletteDelay(const uint16_t& delay);
    void setPaletteStretch(const uint8_t& stretch);
    void setPaletteBlending(const bool& blending);

private:
    CRGB _leds[LED_COUNT];

    Mode _currentMode = Mode::COLOR;
    CRGB _currentColor = CRGB(255, 255, 255);
    uint8_t _scrollingColorIndex = 0;
    uint8_t _brightness = 255;
    unsigned long _lastUpdate = 0;

    PaletteConfig _paletteConfig = PaletteConfig { 
        palette: RainbowColors_p,
        mode: PaletteMode::SCROLLING,
        delay: 10,
        stretch: 3,
        blending: TBlendType::LINEARBLEND,
    };

    void setPaletteStaticColor();
};

#endif
