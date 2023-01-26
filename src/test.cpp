#include "test.h"
#include "Arduino.h"

Test::Test() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void Test::hello() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
