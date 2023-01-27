#include "commands/colorcommand.h"

ColorCommand::ColorCommand(LEDController* controller): Command(controller) {}

void ColorCommand::receivedInput(const uint8_t* input[], const uint8_t& len) {
    if(len < 4) return;
    const CRGB color(*input[1], *input[2], *input[3]);
}
