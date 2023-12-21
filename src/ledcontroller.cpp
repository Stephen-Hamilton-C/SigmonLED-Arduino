#include "ledcontroller.h"

LEDController::LEDController() {
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(
        _leds, LED_COUNT
    ).setCorrection(LED_COLOR_CORRECTION);
    
    setColor(CRGB::White);
    setBrightness(0);
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
                updateStrip();
                break;
            }
            case PaletteMode::SOLID: {
                for(int i = 0; i < LED_COUNT; i++) {
                    _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
                }
                colorIndex += _paletteConfig.stretch;
                updateStrip();
                break;
            }
            case PaletteMode::STATIC: return; // Do nothing for STATIC as it will be set when palettes and modes are set
        }

        _lastUpdate = currentMillis;
    }
}

void LEDController::setMode(const Mode &mode) {
    _currentMode = mode;
    if(_currentMode == Mode::COLOR) {
        updateStrip();
    } else {
        setBrightness(_brightness);
    }
}

void LEDController::setColor(const CRGB &color) {
    _currentColor = color;
    for (int i = 0; i < LED_COUNT; i++) {
        _leds[i] = color;
    }
    if(_brightness == 0) {
        setBrightness(255);
    }
    updateStrip();
}

void LEDController::setBrightness(const uint8_t &brightness) {
    _brightness = brightness;
    FastLED.setBrightness(brightness);
    updateStrip();
}

void LEDController::setPalette(const PaletteType& type) {
    switch(type) {
        case PaletteType::RAINBOW:
            _paletteConfig.palette = RainbowColors_p;
            break;
        case PaletteType::RAINBOW_STRIPE:
            _paletteConfig.palette = RainbowStripeColors_p;
            break;
        case PaletteType::PARTY:
            _paletteConfig.palette = PartyColors_p;
            break;
        case PaletteType::OCEAN:
            _paletteConfig.palette = OceanColors_p;
            break;
        case PaletteType::LAVA:
            _paletteConfig.palette = LavaColors_p;
            break;
        case PaletteType::FOREST:
            _paletteConfig.palette = ForestColors_p;
            break;
        default:
            _paletteConfig.palette = customPalette;
            break;
    }
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

void LEDController::setGradient(const CRGB& start, const CRGB& end) {
    setMode(Mode::COLOR);

    // Could end up with divide by zero if there's only one LED
    if(LED_COUNT == 1) {
        _leds[0] = start;
        updateStrip();
        return;
    }

    _leds[0] = start;
    for(int i = 1; i < LED_COUNT - 1; i++) {
        _leds[i] = CRGB(
            calculateGradientPixel(i, end.r, start.r),
            calculateGradientPixel(i, end.g, start.g),
            calculateGradientPixel(i, end.b, start.b)
        );
    }
    _leds[LED_COUNT - 1] = end;
    updateStrip();
}

uint8_t LEDController::calculateGradientPixel(const int i, const uint8_t final, const uint8_t initial) {
    int16_t change = final - initial;
    int changePerPixel = change / (LED_COUNT - 1);
    int result = initial + (changePerPixel * i);
    if(result < 0) {
        result *= -1;
    }
    return result;
}

void LEDController::distributePalette(const CRGBPalette16& palette) {
    setMode(Mode::COLOR);

    // Could end up with divide by zero if there's only one LED
    if(LED_COUNT == 1) {
        _leds[0] = ColorFromPalette(palette, 0);
        updateStrip();
        return;
    }

    // colorIndex = 0 - 255
    // i / LED_COUNT = percentage
    // 255 * percentage
    for(int i = 0; i < LED_COUNT; i++) {
        float percentage = (float)i / (LED_COUNT - 1);
        _leds[i] = ColorFromPalette(palette, 255 * percentage);
    }
    updateStrip();
}

void LEDController::setPaletteStaticColor() {
    if(_paletteConfig.mode != PaletteMode::STATIC) return;

    uint8_t colorIndex = 0;
    for(int i = 0; i < LED_COUNT; i++) {
        _leds[i] = ColorFromPalette(_paletteConfig.palette, colorIndex, 255, _paletteConfig.blending);
        colorIndex += _paletteConfig.stretch;
    }
    updateStrip();
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

void LEDController::updateStrip() {
    updateQueued = true;
}

void LEDController::forceUpdate() {
    updateQueued = false;
    FastLED.show();
}
