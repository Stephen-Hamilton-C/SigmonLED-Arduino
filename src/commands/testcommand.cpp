#include "commands/testcommand.h"

#include <Arduino.h>

void TestCommand::run(char** command, LEDController& controller) {
    Serial.print("Test: ");
    Serial.println(command[0]);
}
