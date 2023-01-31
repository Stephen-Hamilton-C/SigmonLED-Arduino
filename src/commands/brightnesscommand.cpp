#include "commands/brightnesscommand.h"

BrightnessCommand::BrightnessCommand(LEDController& controller): Command(controller) {}

void BrightnessCommand::fire(uint8_t* argArray) {
    const uint8_t brightness = argArray[1];
    _controller.setBrightness(brightness);
}

uint8_t BrightnessCommand::requiredArgs() {
    return 1;
}
