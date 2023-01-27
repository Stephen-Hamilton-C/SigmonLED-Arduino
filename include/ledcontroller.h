#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <FastLED.h>
#include <SoftwareSerial.h>
#include "config.h"

#define LED_PIN 8
#define LED_COUNT 81
#define LED_COLOR_ORDER EOrder::GRB
#define LED_COLOR_CORRECTION LEDColorCorrection::TypicalLEDStrip

class LEDController {
public:
    LEDController(SoftwareSerial* HM10);
    void loop();

    void setColor(const CRGB& color);

    enum Mode {
        Color,
        Palette,
    };

private:
    CRGB _leds[LED_COUNT];
    SoftwareSerial* _HM10;

    Mode _currentMode = Mode::Color;
    CRGB _currentColor = CRGB(255, 255, 255);
};

#endif
