#include "commands/blendingcommand.h"

#include "util.h"

void BlendingCommand::run(char** command, LEDController* controller) {
    bool blendType = Util::parseASCIINumber(command[1]);
    controller->setPaletteBlending(blendType);
}
