#include "commands/hellocommand.h"

void HelloCommand::run(char** command, LEDController& controller) {
    // Version, Color, Mode, Brightness,
    // Palette type, Palette mode, Palette delay, Palette stretch, Palette blending
    // Version
    Serial.print(VERSION);
    Serial.print(' ');

    // Color
    CRGB color = controller.getColor();
    Serial.print(color.r);
    Serial.print(',');
    Serial.print(color.g);
    Serial.print(',');
    Serial.print(color.b);
    Serial.print(' ');

    // Mode
    // COLOR = 0
    // PALETTE = 1
    Serial.print(controller.getMode());
    Serial.print(' ');

    // Brightness
    Serial.print(controller.getBrightness());
    Serial.print(' ');

    PaletteConfig config = controller.getPaletteConfig();
    // Palette type
    // RAINBOW = 0
    // RAINBOW_STRIPE = 1
    // PARTY = 2
    // OCEAN = 3
    // LAVA = 4
    // FOREST = 5
    // CUSTOM = 6
    Serial.print(config.type);
    Serial.print(' ');

    // Palette delay
    Serial.print(config.delay);
    Serial.print(' ');

    // Palette stretch
    Serial.print(config.stretch);
    Serial.print(' ');

    // Palette blending
    // NOBLEND = 0
    // LINEARBLEND = 1
    // LINEARBLEND_NOWRAP = 2
    Serial.println(config.blending);
}
