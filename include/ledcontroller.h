#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <FastLED.h>
#include <SoftwareSerial.h>
#include "config.h"

class LEDController {
public:
    LEDController();
    void loop();

    void setColor(const CRGB& color);

    enum Mode {
        Color,
        Palette,
    };

private:
    CRGB _leds[LED_COUNT];

    Mode _currentMode = Mode::Color;
    CRGB _currentColor = CRGB(255, 255, 255);
};

#endif
