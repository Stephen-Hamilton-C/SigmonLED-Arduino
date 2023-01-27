#include "commands/commandhandler.h"
#include "commands/palettecommand.h"

CommandHandler::CommandHandler(LEDController* controller) {
    _controller = controller;
}

void CommandHandler::handle(const uint8_t* readBuffer[], uint8_t& len) {
    if(len == 0) return;

    const uint8_t* desiredCmd = readBuffer[0];
    Command* command;
    switch(*desiredCmd) {
        case 'p':
            command = new PaletteCommand(_controller);
            break;
    }
    command->receivedInput(readBuffer, len);
}
