#include "commands/colorcommand.h"

void ColorCommand::getName(char out[NAME_LEN]) {
    strcpy(out, "color");
}

int ColorCommand::getArgCount() {
    return 3;
}

void ColorCommand::run(char** arguments, LEDController& controller) {
    Serial.print("arg0: ");
    Serial.println(arguments[0]);
    Serial.print("arg1: ");
    Serial.println(arguments[1]);
    Serial.print("arg2: ");
    Serial.println(arguments[2]);
    Serial.print("arg3: ");
    Serial.println(arguments[3]);
}
