#include "commands/palettecommand.h"
#include "paletteparser.h"
#include "paletteconfig.h"
#include "palettemode.h"

PaletteCommand::PaletteCommand(LEDController& controller): Command(controller) {}

void PaletteCommand::receivedInput(const uint8_t (&input)[READ_BUFFER_SIZE], const uint8_t& len) {
    if(len < 2) return;
    const uint8_t rawPaletteMode = input[0];
    PaletteMode paletteMode;
    switch(rawPaletteMode) {
        case 'p': {
            Serial.println("Received SCROLLING mode");
            paletteMode = PaletteMode::SCROLLING;
            break;
        }
        case 'P': {
            Serial.println("Received SOLID mode");
            paletteMode = PaletteMode::SOLID;
            break;
        }
        case 's': {
            Serial.println("Received STATIC mode");
            paletteMode = PaletteMode::STATIC;
            break;
        }
        default: return; // Unknown palette mode
    }

    const uint8_t rawPalette = input[1];
    CRGBPalette16 palette = PaletteParser::parseToPalette(rawPalette);

    _controller.setPalette(palette);
    _controller.setPaletteMode(paletteMode);
    _controller.setMode(LEDController::Mode::PALETTE);
}
