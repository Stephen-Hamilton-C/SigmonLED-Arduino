// The original code for SigmonLED was a basic Arduino project.
// This was fine for the rapid prototyping I was doing,
// but I have further ambitions that would further SigmonLED.

#include <Arduino.h>
#include "test.h"

Test test;

void setup() {
    test = Test();
}

void loop() {
    test.hello();
}
