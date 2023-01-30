#include "commands/inputhandler.h"
#include "commands/blendingcommand.h"
#include "commands/brightnesscommand.h"
#include "commands/colorcommand.h"
#include "commands/delaycommand.h"
#include "commands/palettecommand.h"
#include "commands/palettemodecommand.h"
#include "commands/stretchcommand.h"

InputHandler::InputHandler(LEDController& controller): _controller(controller) {}

void InputHandler::nextByte(const uint8_t rxByte) {
    if(_nextCommand == nullptr) {
        switch(rxByte) {
            case 'c':
                _nextCommand = new ColorCommand(_controller);
                break;
            case 'p':
                _nextCommand = new PaletteCommand(_controller);
                break;
            case 'P':
                _nextCommand = new PaletteModeCommand(_controller);
                break;
            case 'l':
                _nextCommand = new BlendingCommand(_controller);
                break;
            case 'b':
                _nextCommand = new BrightnessCommand(_controller);
                break;
            case 'd':
                _nextCommand = new DelayCommand(_controller);
                break;
            case 's':
                _nextCommand = new StretchCommand(_controller);
                break;
            default:
                // Unrecognized command
                return;
            fireCommandForArgs(); // Cover cases where commands have 0 args
        }
    } else {
        if(_bufferLen >= BUFFER_SIZE) {
            // Buffer overflow, reset
            reset();
        } else {
            // Add this input to argument buffer
            _buffer[_bufferLen] = rxByte;
            _bufferLen++;
            fireCommandForArgs();
        }
    }

    // If multiple bytes came in a single loop, we should try to read them all
    if(Serial.available()) {
        nextByte(Serial.read());
    }
}

void InputHandler::fireCommandForArgs() {
    if(_nextCommand->requiredArgs() <= _bufferLen) {
        Serial.println(_bufferLen);
        _nextCommand->fire(_buffer);
        reset();
    }
}

void InputHandler::reset() {
    _nextCommand = nullptr;
    _bufferLen = 0;
}
