#include "commands/stretchcommand.h"

StretchCommand::StretchCommand(LEDController& controller): Command(controller) {}

void StretchCommand::fire(uint8_t* argArray) {
    const uint8_t stretch = argArray[0];
    _controller.setPaletteStretch(stretch);
}

uint8_t StretchCommand::requiredArgs() {
    return 1;
}
