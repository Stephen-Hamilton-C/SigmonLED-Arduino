// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
#include "messagehandler.h"
#include "config.h"

MessageHandler msgHandler;
char buffer[MESSAGE_BUFFER];
int bufferLen = 0;

void setup() {
    // Setup Serial interfaces
    Serial.begin(SERIAL_BAUD);

    // Disable the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    // Handle input
    while(Serial.available()) {
        char nextChar = Serial.read();
        buffer[bufferLen++] = nextChar;
        #if ECHO
            Serial.print(nextChar);
        #endif

        if(nextChar == '\n') {
            // End of message
            buffer[bufferLen++] = '\0';
            msgHandler.processMessage(buffer, bufferLen);
            bufferLen = 0;
        } else if(bufferLen >= MESSAGE_BUFFER - 2) {
            // Buffer overflow, ignore
            bufferLen = 0;
        }
    }

    msgHandler.loop();
}
