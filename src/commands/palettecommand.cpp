#include "commands/palettecommand.h"
#include "paletteparser.h"

PaletteCommand::PaletteCommand(LEDController& controller): Command(controller) {}

void PaletteCommand::receivedInput(const uint8_t (&input)[READ_BUFFER_SIZE], const uint8_t& len) {
    if(len < 2) return;
    const uint8_t desiredPalette = input[1];
    CRGBPalette16 palette = PaletteParser::parseToPalette(desiredPalette);
}
