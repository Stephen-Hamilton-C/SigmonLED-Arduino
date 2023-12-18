#include "commands/brightnesscommand.h"

#include "util.h"

void BrightnessCommand::run(char** command, LEDController& controller) {
    uint8_t brightness = Util::parseASCIINumber(command[1]);
    controller.setBrightness(brightness);
}
