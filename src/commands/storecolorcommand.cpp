#include "commands/storecolorcommand.h"
#include "commands/oncommand.h"

StoreColorCommand::StoreColorCommand(LEDController& controller): Command(controller) {}

void StoreColorCommand::fire(uint8_t* argArray) {
    const uint8_t r = argArray[1];
    const uint8_t g = argArray[2];
    const uint8_t b = argArray[3];

    OnCommand::storedColor = CRGB(r, g, b);
}

uint8_t StoreColorCommand::requiredArgs() {
    return 3;
}
