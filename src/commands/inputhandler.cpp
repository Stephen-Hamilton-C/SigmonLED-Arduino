#include "commands/inputhandler.h"
#include "commands/blendingcommand.h"
#include "commands/brightnesscommand.h"
#include "commands/colorcommand.h"
#include "commands/custompalettecommand.h"
#include "commands/delaycommand.h"
#include "commands/offcommand.h"
#include "commands/oncommand.h"
#include "commands/palettecommand.h"
#include "commands/palettemodecommand.h"
#include "commands/storecolorcommand.h"
#include "commands/stretchcommand.h"

InputHandler::InputHandler(LEDController& controller): _controller(controller) {}

void InputHandler::loop() {
    const unsigned long currentMillis = millis();
    const unsigned long timeSinceLastByte = currentMillis - _timeOfLastByte;

    if(timeSinceLastByte > BUFFER_TIMEOUT) {
        _bufferLen = 0;
    }

    if(_connected && timeSinceLastByte > CONNECTION_TIMEOUT) {
        _connected = false;
        Serial.write("AT");
    }
}

void InputHandler::processByte(const uint8_t byte) {
    Serial.println(byte); // I don't understand it, but leaving these in somehow prevents the Arduino from locking up
    if(_bufferLen < BUFFER_SIZE - 1) {
        _buffer[_bufferLen++] = byte;
    } else {
        // Buffer overflow, reset
        _bufferLen = 0;
        return;
    }

    if(byte == '\n') {
        Serial.println(); // I don't understand it, but leaving these in somehow prevents the Arduino from locking up
        // Terminator received, process line
        Command* cmd = getCommand(_buffer[0]);
        if(cmd != nullptr) {
            if(_bufferLen-1 >= cmd->requiredArgs()) {
                cmd->fire(_buffer);
            }
        }

        _bufferLen = 0;
    }

    _timeOfLastByte = millis();
    _connected = true;
}

Command* InputHandler::getCommand(const uint8_t& cmdByte) {
    switch(cmdByte) {
        case 'l': return new BlendingCommand(_controller);
        case 'b': return new BrightnessCommand(_controller);
        case 'c': return new ColorCommand(_controller);
        case 'C': return new CustomPaletteCommand(_controller);
        case 'd': return new DelayCommand(_controller);
        case '0': return new OffCommand(_controller);
        case '1': return new OnCommand(_controller);
        case 'p': return new PaletteCommand(_controller);
        case 'P': return new PaletteModeCommand(_controller);
        case 'S': return new StoreColorCommand(_controller);
        case 's': return new StretchCommand(_controller);
    }

    return nullptr;
}
