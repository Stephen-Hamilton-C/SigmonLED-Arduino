#include "commands/colorcommand.h"

#include <Arduino.h>
#include "util.h"

void ColorCommand::run(char** command, LEDController* controller) {
    int red = Util::parseASCIINumber(command[1]);
    int green = Util::parseASCIINumber(command[2]);
    int blue = Util::parseASCIINumber(command[3]);
    controller->setColor(CRGB(red, green, blue));
    controller->setMode(LEDController::Mode::COLOR);
}
