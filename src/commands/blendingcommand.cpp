#include "commands/blendingcommand.h"

BlendingCommand::BlendingCommand(LEDController& controller): Command(controller) {}

void BlendingCommand::fire(uint8_t* argArray) {
    const uint8_t blending = argArray[0];
    _controller.setPaletteBlending(blending);
}

uint8_t BlendingCommand::requiredArgs() {
    return 1;
}
