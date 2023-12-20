#include "irhandler.h"
#include <IRremote.h>
#include "irmapping.h"

IRrecv* irReceiver;

IRHandler::IRHandler(LEDController* controller) {
    _controller = controller;

    irReceiver = new IRrecv(IR_PIN);
    irReceiver->start();
}

bool IRHandler::isIdle() {
    return IrReceiver.isIdle();
}

void IRHandler::printInput(const uint32_t input) {
    if(!ECHO) return;
    switch(input) {
        case IRIN_1:
            Serial.println("IR: 1");
            break;
        case IRIN_2:
            Serial.println("IR: 2");
            break;
        case IRIN_3:
            Serial.println("IR: 3");
            break;
        case IRIN_4:
            Serial.println("IR: 4");
            break;
        case IRIN_5:
            Serial.println("IR: 5");
            break;
        case IRIN_6:
            Serial.println("IR: 6");
            break;
        case IRIN_7:
            Serial.println("IR: 7");
            break;
        case IRIN_8:
            Serial.println("IR: 8");
            break;
        case IRIN_9:
            Serial.println("IR: 9");
            break;
        case IRIN_0:
            Serial.println("IR: 0");
            break;
        case IRIN_COLOR:
            Serial.println("IR: *");
            break;
        case IRIN_MODE:
            Serial.println("IR: #");
            break;
        case IRIN_LEFT:
            Serial.println("IR: <");
            break;
        case IRIN_RIGHT:
            Serial.println("IR: >");
            break;
        case IRIN_UP:
            Serial.println("IR: ^");
            break;
        case IRIN_DOWN:
            Serial.println("IR: v");
            break;
        case IRIN_OK:
            Serial.println("IR: OK");
            break;
        case IRIN_REPEAT:
            Serial.println("IR: REPEAT");
            break;
        default:
            Serial.print("IR: Unknown: ");
            Serial.println(input, HEX);
            break;
    }
}

void IRHandler::loop() {
    if(irReceiver->decode()) {
        if(irReceiver->decodedIRData.decodedRawData == IRIN_REPEAT) {
            if(millis() - _lastDataTimestamp >= 500) {
                irReceiver->resume();
                return;
            }
        } else {
            _lastInput = irReceiver->decodedIRData.decodedRawData;
        }
        _lastDataTimestamp = millis();
        printInput(irReceiver->decodedIRData.decodedRawData);
        handleInput(irReceiver->decodedIRData.decodedRawData);
        irReceiver->resume();
    }
}

void IRHandler::handleInput(const uint32_t input) {
    // TODO:
    // if(off) {
    //     turnOn();
    //     return;
    // }

    switch(_lastInput) {
        case IRIN_1:
            // 1
            handleDigit(1);
            break;
        case IRIN_2:
            // 2
            handleDigit(2);
            break;
        case IRIN_3:
            // 3
            handleDigit(3);
            break;
        case IRIN_4:
            // 4
            handleDigit(4);
            break;
        case IRIN_5:
            // 5
            handleDigit(5);
            break;
        case IRIN_6:
            // 6
            handleDigit(6);
            break;
        case IRIN_7:
            // 7
            handleDigit(7);
            break;
        case IRIN_8:
            // 8
            handleDigit(8);
            break;
        case IRIN_9:
            // 9
            handleDigit(9);
            break;
        case IRIN_0:
            // 0
            handleDigit(10);
            break;
        case IRIN_COLOR:
            // COLOR
            handleColor();
            break;
        case IRIN_MODE:
            // MODE
            handleSwitchMode();
            break;
        case IRIN_LEFT:
            // LEFT
            handleSwitchValueType(-1);
            break;
        case IRIN_RIGHT:
            // RIGHT
            handleSwitchValueType(1);
            break;
        case IRIN_UP:
            // UP
            handleValueIncrement(1);
            break;
        case IRIN_DOWN:
            // DOWN
            handleValueIncrement(-1);
            break;
        case IRIN_OK:
            // OK
            // TODO: turnOff();
            break;
    }
}

void IRHandler::handleDigit(const uint8_t digit) {
    _incrementMagnitude = digit;
}

void IRHandler::handleValueIncrement(const int8_t direction) {
    switch(_currentType) {
        case BRIGHTNESS: {
            // Don't need to worry about wraparound in this case
            uint8_t brightness = _controller->getBrightness();
            _controller->setBrightness(brightness + (direction * _incrementMagnitude));
            break;
        }
        case PALETTE_TYPE: {
            PaletteConfig config = _controller->getPaletteConfig();
            PaletteType type = config.type;
            if(type <= 0 && direction < 0) {
                type = PALETTETYPE_MAX;
            } else if(type >= PALETTETYPE_MAX && direction > 0) {
                type = 0;
            } else {
                type += direction;
            }

            _controller->setPalette(type);
            break;
        }
    }
}

void IRHandler::handleSwitchValueType(const int8_t direction) {
    switch(_controller->getMode()) {
        case LEDController::Mode::PALETTE: {
            if(_currentType <= 0 && direction < 0) {
                _currentType = VALUETYPE_MAX;
            } else if(_currentType >= VALUETYPE_MAX && direction > 0) {
                _currentType = 0;
            } else {
                _currentType += direction;
            }
            break;
        }
        case LEDController::Mode::COLOR_SELECT: {
            // TODO
            break;
        }
    }
}

void IRHandler::handleSwitchMode() {
    if(_controller->getMode() == LEDController::Mode::COLOR_SELECT) return;
}

void IRHandler::handleColor() {
    // TODO
}
