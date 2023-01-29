#include "commands/commandhandler.h"
#include "commands/colorcommand.h"
#include "commands/palettecommand.h"

CommandHandler::CommandHandler(LEDController& controller): _controller(controller) {}

void CommandHandler::handle(const uint8_t (&readBuffer)[READ_BUFFER_SIZE], uint8_t& len) {
    if(len == 0) return;

    Serial.println("Handling command");
    const uint8_t desiredCmd = readBuffer[0];
    Command* command = nullptr;
    switch(desiredCmd) {
        case 'c':
            Serial.println("Color");
            command = new ColorCommand(_controller);
            break;
        case 'p':
        case 'P':
        case 's':
            Serial.println("Palette");
            command = new PaletteCommand(_controller);
            break;
        default:
            Serial.println("No matching commands:");
            Serial.println((char)desiredCmd);
            break;
    }
    if(command != nullptr) {
        Serial.println("Command is not null, running");
        command->receivedInput(readBuffer, len);
    }
}
