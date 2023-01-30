// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
#include "commands/inputhandler.h"
#include "ledcontroller.h"

LEDController* controller;
InputHandler* handler;

void setup() {
    // Setup Serial interfaces
    Serial.begin(9600);
    Serial.println("Hello, world!");

    // Prepare LEDs
    controller = new LEDController();
    handler = new InputHandler(*controller);

    // Disable the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    // Handle input
    if(Serial.available()) {
        handler->nextByte(Serial.read());
    }

    controller->loop();
}
