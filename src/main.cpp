// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
#include "irmapping.h"
#include <IRremote.h>
#include "messagehandler.h"
#include "config.h"

IRrecv irReceiver(IR_PIN);
MessageHandler* msgHandler;
LEDController* ledController;
char buffer[MESSAGE_BUFFER];
int bufferLen = 0;
unsigned long lastMessageTimestamp = 0;
bool connected = false;

void setup() {
    // Setup Serial interfaces
    Serial.begin(SERIAL_BAUD);
    // TODO: Can command message handler coexist with IR?
    ledController = new LEDController();
    msgHandler = new MessageHandler(ledController);

    // Disable the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    irReceiver.start();
}

void loop() {
    // Handle input
    if(ledController->updateQueued && IrReceiver.isIdle()) {
        ledController->updateQueued = false;
        FastLED.show();
    }

    // Remote input from IR
    if(irReceiver.decode()) {
        switch(irReceiver.decodedIRData.decodedRawData) {
            case IRIN_1:
                Serial.println("1");
                break;
            case IRIN_2:
                Serial.println("2");
                break;
            case IRIN_3:
                Serial.println("3");
                break;
            case IRIN_4:
                Serial.println("4");
                break;
            case IRIN_5:
                Serial.println("5");
                break;
            case IRIN_6:
                Serial.println("6");
                break;
            case IRIN_7:
                Serial.println("7");
                break;
            case IRIN_8:
                Serial.println("8");
                break;
            case IRIN_9:
                Serial.println("9");
                break;
            case IRIN_0:
                Serial.println("0");
                break;
            case IRIN_COLOR:
                Serial.println("*");
                break;
            case IRIN_MODE:
                Serial.println("#");
                break;
            case IRIN_LEFT:
                Serial.println("<");
                break;
            case IRIN_RIGHT:
                Serial.println(">");
                break;
            case IRIN_UP:
                Serial.println("^");
                break;
            case IRIN_DOWN:
                Serial.println("v");
                break;
            case IRIN_OK:
                Serial.println("OK");
                break;
            case IRIN_REPEAT:
                Serial.println("REPEAT");
                break;
            default:
                Serial.print("Unknown: ");
                Serial.println(irReceiver.decodedIRData.decodedRawData, HEX);
                break;
        }
        irReceiver.resume();
    }

    // Command input from Serial
    while(Serial.available()) {
        connected = true;
        lastMessageTimestamp = millis();

        char nextChar = Serial.read();
        buffer[bufferLen++] = nextChar;
        #if ECHO
            Serial.print(nextChar);
        #endif

        if(nextChar == '\n') {
            // End of message
            buffer[bufferLen++] = '\0';
            msgHandler->processMessage(buffer, bufferLen);
            bufferLen = 0;
        } else if(bufferLen >= MESSAGE_BUFFER - 2) {
            // Buffer overflow, ignore
            bufferLen = 0;
        }
    }

    if(connected && millis() - lastMessageTimestamp >= CONNECTION_TIMEOUT) {
        if(TIMEOUT_MESSAGE != 0) {
            Serial.print(TIMEOUT_MESSAGE);
        }
        connected = false;
    }

    msgHandler->loop();
}
