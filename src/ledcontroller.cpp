#include "ledcontroller.h"

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(
        _leds, LED_COUNT
    ).setCorrection(LED_COLOR_CORRECTION);
    
    // TODO: Remove this when BrightnessCommand is done
    FastLED.setBrightness(32);

    setColor(CRGB::Black);
}

void LEDController::loop() {
    if(_currentMode == Mode::PALETTE)
        paletteLoop();
}

void LEDController::paletteLoop() {
    uint8_t colorIndex = ++_scrollingColorIndex;

    switch(_paletteConfig.mode) {
        case PaletteMode::SCROLLING: {
            for(int i = 0; i < LED_COUNT; i++) {
                _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
                colorIndex += _paletteConfig.stretch;
            }
            FastLED.show();
            delay(_paletteConfig.delay); // TODO: Use timer instead of delay
            break;
        }
        case PaletteMode::SOLID: {
            for(int i = 0; i < LED_COUNT; i++) {
                _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
            }
            colorIndex += _paletteConfig.stretch;
            FastLED.show();
            delay(_paletteConfig.delay); // TODO: Use timer instead of delay
            break;
        }
        case PaletteMode::STATIC: return; // Do nothing for STATIC as it will be set when palettes and modes are set
    }
}

void LEDController::setMode(const Mode &mode) {
    _currentMode = mode;
}

void LEDController::setColor(const CRGB &color) {
    _currentColor = color;
    for (int i = 0; i < LED_COUNT; i++) {
        _leds[i] = color;
    }
    FastLED.show();
}

void LEDController::setBrightness(const uint8_t &brightness) {
    _brightness = brightness;
    FastLED.setBrightness(brightness);
    FastLED.show();
}

void LEDController::setPalette(const CRGBPalette16 &palette) {
    Serial.println("Set palette");
    _paletteConfig.palette = palette;
    setPaletteStaticColor();
}

void LEDController::setPaletteMode(const PaletteMode &mode) {
    _paletteConfig.mode = mode;
    Serial.print("Set palette mode to ");
    Serial.println(mode);
    setPaletteStaticColor();
}

void LEDController::setPaletteDelay(const uint16_t &delay) {
    _paletteConfig.delay = delay;
}

void LEDController::setPaletteBlending(const bool &blending) {
    _paletteConfig.blending = blending ? TBlendType::LINEARBLEND : TBlendType::NOBLEND;
    setPaletteStaticColor();
}

void LEDController::setPaletteStaticColor() {
    if(_paletteConfig.mode != PaletteMode::STATIC) return;

    // TODO: I need to do math ;-;
    // We need to equally distribute the 16 palette colors across LED_COUNT leds
    uint8_t colorIndex = 0;
    for(int i = 0; i < LED_COUNT; i++) {
        _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
        colorIndex+=10;
    }
    FastLED.show();
}