#include "commands/delaycommand.h"

#include "util.h"

void DelayCommand::run(char** command, LEDController& controller) {
    uint16_t delay = Util::parseASCIINumber(command[1]);
    controller.setPaletteDelay(delay);
}
