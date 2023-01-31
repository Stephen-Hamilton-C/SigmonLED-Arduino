#include "commands/inputhandler.h"
#include "commands/blendingcommand.h"
#include "commands/brightnesscommand.h"
#include "commands/colorcommand.h"
#include "commands/delaycommand.h"
#include "commands/palettecommand.h"
#include "commands/palettemodecommand.h"
#include "commands/stretchcommand.h"

InputHandler::InputHandler(LEDController& controller): _controller(controller) {}

void InputHandler::loop() {
    const unsigned long currentMillis = millis();
    if(currentMillis - _timeOfLastByte > BUFFER_TIMEOUT) {
        _bufferLen = 0;
    }
}

void InputHandler::processByte(const uint8_t byte) {
    if(_bufferLen < BUFFER_SIZE - 1) {
        _buffer[_bufferLen++] = byte;
    } else {
        // Buffer overflow, reset
        _bufferLen = 0;
        return;
    }

    if(byte == '\n') {
        // Terminator received, process line
        Command* cmd = getCommand(_buffer[0]);
        if(cmd != nullptr) {
            if(_bufferLen >= cmd->requiredArgs()) {
                cmd->fire(_buffer);
            }
        }

        _bufferLen = 0;
    }

    _timeOfLastByte = millis();
}

Command* InputHandler::getCommand(const uint8_t& cmdByte) {
    switch(cmdByte) {
        case 'c': return new ColorCommand(_controller);
        case 'p': return new PaletteCommand(_controller);
        case 'P': new PaletteModeCommand(_controller);
        case 'l': new BlendingCommand(_controller);
        case 'b': new BrightnessCommand(_controller);
        case 'd': new DelayCommand(_controller);
        case 's': new StretchCommand(_controller);
        default: return nullptr;
    }
}
