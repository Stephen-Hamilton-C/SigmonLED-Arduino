// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
#include <IRremote.h>
#include "messagehandler.h"
#include "config.h"

IRrecv irReceiver(IR_PIN);
MessageHandler* msgHandler;
char buffer[MESSAGE_BUFFER];
int bufferLen = 0;
unsigned long lastMessageTimestamp = 0;
bool connected = false;

void setup() {
    // Setup Serial interfaces
    Serial.begin(SERIAL_BAUD);
    // TODO: Can command message handler coexist with IR?
    msgHandler = new MessageHandler();

    // Disable the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    irReceiver.start();
}

void loop() {
    // Handle input
    if(msgHandler->getController().updateQueued && IrReceiver.isIdle()) {
        msgHandler->getController().updateQueued = false;
        FastLED.show();
    }

    // Remote input from IR
    if(irReceiver.decode()) {
        Serial.println(irReceiver.decodedIRData.decodedRawData, HEX);
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
