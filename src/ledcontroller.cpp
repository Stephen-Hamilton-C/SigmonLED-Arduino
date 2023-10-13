#include "ledcontroller.h"

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(
        _leds, LED_COUNT
    ).setCorrection(LED_COLOR_CORRECTION);
    
    setColor(CRGB::Black);
}

void LEDController::loop() {
    if(_currentMode == Mode::PALETTE)
        paletteLoop();
}

void LEDController::paletteLoop() {
    const unsigned long currentMillis = millis();

    if(currentMillis - _lastUpdate >= _paletteConfig.delay) {
        uint8_t colorIndex = ++_scrollingColorIndex;

        switch(_paletteConfig.mode) {
            case PaletteMode::SCROLLING: {
                for(int i = 0; i < LED_COUNT; i++) {
                    _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
                    colorIndex += _paletteConfig.stretch;
                }
                FastLED.show();
                break;
            }
            case PaletteMode::SOLID: {
                for(int i = 0; i < LED_COUNT; i++) {
                    _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
                }
                colorIndex += _paletteConfig.stretch;
                FastLED.show();
                break;
            }
            case PaletteMode::STATIC: return; // Do nothing for STATIC as it will be set when palettes and modes are set
        }
    }
}

void LEDController::setMode(const Mode &mode) {
    _currentMode = mode;
    if(_currentMode == Mode::COLOR) {
        FastLED.setBrightness(255);
        FastLED.show();
    } else {
        setBrightness(_brightness);
    }
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

void LEDController::setPalette(const CRGBPalette16 &palette, const PaletteType& type) {
    _paletteConfig.palette = palette;
    _paletteConfig.type = type;
    setPaletteStaticColor();
}

void LEDController::setPaletteMode(const PaletteMode &mode) {
    _paletteConfig.mode = mode;
    setPaletteStaticColor();
}

void LEDController::setPaletteDelay(const uint16_t &delay) {
    _paletteConfig.delay = delay;
}

void LEDController::setPaletteStretch(const uint8_t &stretch) {
    _paletteConfig.stretch = stretch;
    setPaletteStaticColor();
}

void LEDController::setPaletteBlending(const bool &blending) {
    _paletteConfig.blending = blending ? TBlendType::LINEARBLEND : TBlendType::NOBLEND;
    setPaletteStaticColor();
}

void LEDController::setPaletteStaticColor() {
    if(_paletteConfig.mode != PaletteMode::STATIC) return;

    uint8_t colorIndex = 0;
    for(int i = 0; i < LED_COUNT; i++) {
        _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
        colorIndex += _paletteConfig.stretch;
    }
    FastLED.show();
}

const LEDController::Mode LEDController::getMode() {
    return _currentMode;
}

const CRGB LEDController::getColor() {
    return _currentColor;
}

const uint8_t LEDController::getBrightness() {
    return _brightness;
}

const PaletteConfig& LEDController::getPaletteConfig() {
    return _paletteConfig;
}
