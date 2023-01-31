#include "commands/delaycommand.h"

DelayCommand::DelayCommand(LEDController& controller): Command(controller) {}

void DelayCommand::fire(uint8_t* argArray) {
    const uint8_t delayByte1 = argArray[1];
    const uint8_t delayByte2 = argArray[2];

    // Source: https://stackoverflow.com/a/11193978
    const uint16_t delay = (delayByte1 << 8) | delayByte2;
    _controller.setPaletteDelay(delay);
}

uint8_t DelayCommand::requiredArgs() {
    return 2;
}
