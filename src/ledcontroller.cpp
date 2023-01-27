#include "ledcontroller.h"

LEDController::LEDController(SoftwareSerial* HM10) {
    _HM10 = HM10;

    // TODO: Figure out why addLeds won't take Config consts
    // TODO: Figure out how to stuff WS2811 into a Config const
    FastLED.addLeds<WS2811, LED_PIN, LED_COLOR_ORDER>(
        _leds, LED_COUNT
    ).setCorrection(LED_COLOR_CORRECTION);
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
    FastLED.showColor(_currentColor);
    // TODO: Is this line necessary?
    FastLED.show();
}
