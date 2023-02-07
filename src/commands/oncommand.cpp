#include "commands/oncommand.h"

CRGB OnCommand::storedColor = CRGB(255, 255, 255);

OnCommand::OnCommand(LEDController& controller): Command(controller) {}

void OnCommand::fire(uint8_t* argArray) {
    _controller.setColor(storedColor);
    _controller.setMode(LEDController::Mode::COLOR);
}

uint8_t OnCommand::requiredArgs() {
    return 0;
}
