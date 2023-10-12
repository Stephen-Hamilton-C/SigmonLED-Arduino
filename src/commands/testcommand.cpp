#include "commands/testcommand.h"

#include <Arduino.h>

void TestCommand::run(char** command) {
    Serial.print("Test: ");
    Serial.println(command[0]);
}
