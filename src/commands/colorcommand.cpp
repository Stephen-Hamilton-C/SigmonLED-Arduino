#include "commands/colorcommand.h"

ColorCommand::ColorCommand(LEDController& controller): Command(controller) {}

void ColorCommand::fire(uint8_t* argArray) {
    const uint8_t r = argArray[0];
    const uint8_t g = argArray[1];
    const uint8_t b = argArray[2];

    const CRGB color(r, g, b);
    _controller.setColor(color);
    _controller.setMode(LEDController::Mode::COLOR);
}

uint8_t ColorCommand::requiredArgs() {
    return 3;
}
