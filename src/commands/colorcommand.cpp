#include "commands/colorcommand.h"

#include <Arduino.h>
#include "commands.h"
#include "ledcontroller.h"

void ColorCommand::run(char** command, LEDController& controller) {
    int red = Commands::parseASCIINumber(command[1]);
    int green = Commands::parseASCIINumber(command[2]);
    int blue = Commands::parseASCIINumber(command[3]);
    controller.setColor(CRGB(red, green, blue));
    controller.setMode(LEDController::Mode::COLOR);
}
