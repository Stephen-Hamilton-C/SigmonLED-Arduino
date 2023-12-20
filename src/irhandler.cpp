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

void IRHandler::off() {
    _controller->setColor(CRGB::Black);
}

void IRHandler::handleInput(const uint32_t input) {
    switch(_lastInput) {
        case IRIN_1:
            // 1
            break;
        case IRIN_2:
            // 2
            break;
        case IRIN_3:
            // 3
            break;
        case IRIN_4:
            // 4
            break;
        case IRIN_5:
            // 5
            break;
        case IRIN_6:
            // 6
            break;
        case IRIN_7:
            // 7
            break;
        case IRIN_8:
            // 8
            break;
        case IRIN_9:
            // 9
            break;
        case IRIN_0:
            // 0
            break;
        case IRIN_COLOR:
            // COLOR
            break;
        case IRIN_MODE:
            // MODE
            break;
        case IRIN_LEFT:
            // LEFT
            break;
        case IRIN_RIGHT:
            // RIGHT
            break;
        case IRIN_UP:
            // UP
            break;
        case IRIN_DOWN:
            // DOWN
            break;
        case IRIN_OK:
            // OK
            _controller->distributePalette(RainbowColors_p);
            break;
    }
}
