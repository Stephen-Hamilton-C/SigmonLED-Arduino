#include "commands/offcommand.h"

OffCommand::OffCommand(LEDController& controller): Command(controller) {}

void OffCommand::fire(uint8_t* argArray) {
    _controller.setColor(CRGB::Black);
}

uint8_t OffCommand::requiredArgs() {
    return 0;
}
