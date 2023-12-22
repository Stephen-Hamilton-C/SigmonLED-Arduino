// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
#include "config.h"
#include "ledcontroller.h"


#if ENABLE_SERIAL_COMMANDS
#include "messagehandler.h"
MessageHandler* msgHandler;
#endif
#if ENABLE_IR_INPUT
#include "irhandler.h"
IRHandler* irHandler;
#endif
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
    #if ENABLE_SERIAL_COMMANDS
    msgHandler = new MessageHandler(ledController);
    #endif
    #if ENABLE_IR_INPUT
    irHandler = new IRHandler(ledController);
    #endif

    // Disable the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    // Handle input
    #if ENABLE_IR_INPUT
    if(ledController->updateQueued && irHandler->isIdle()) {
    #else
    if(ledController->updateQueued) {
    #endif
        ledController->updateQueued = false;
        FastLED.show();
    }

#if ENABLE_IR_INPUT
    // Remote input from IR
    irHandler->loop();
#endif

#if ENABLE_SERIAL_COMMANDS
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
#endif
    ledController->loop();
}
