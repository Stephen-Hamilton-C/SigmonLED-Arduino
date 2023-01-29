// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
// Only for debugging, this takes up a chunk of memory and isn't as fast as hardware
#include <SoftwareSerial.h>
#include "constants.h"
#include "commands/commandhandler.h"
#include "ledcontroller.h"

SoftwareSerial HM10(2, 3);
LEDController* controller;
CommandHandler* handler;

void setup() {
    // Setup Serial interfaces
    Serial.begin(9600);
    HM10.begin(SERIAL_BAUD);

    delay(3000);
    Serial.println("Hello, world!");

    // // Prepare LEDs
    controller = new LEDController();
    handler = new CommandHandler(*controller);

    // Disable the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    // Handle input
    if(HM10.available()) {
        uint8_t buffer[READ_BUFFER_SIZE] = {};
        uint8_t len = HM10.readBytesUntil('#', buffer, READ_BUFFER_SIZE);

        handler->handle(buffer, len);
    }

    controller->loop();
}
