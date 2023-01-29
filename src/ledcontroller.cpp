#include "ledcontroller.h"

LEDController::LEDController() {
    // TODO: Figure out why addLeds won't take Config consts
    // TODO: Figure out how to stuff WS2811 into a Config const
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(
        _leds, LED_COUNT
    ).setCorrection(LED_COLOR_CORRECTION);
    
    setColor(CRGB::Black);
}

void LEDController::loop() {
    switch(_currentMode) {
        case Mode::Color: {
            // Do nothing - color will be changed in setColor
            break;
        }
        case Mode::Palette: {
            // TODO: Maybe there should be a PaletteController...
            break;
        }
    }
}

void LEDController::setColor(const CRGB& color) {
    _currentColor = color;
    for (int i = 0; i < LED_COUNT; i++) {
        _leds[i] = color;
    }
    FastLED.show();
}
