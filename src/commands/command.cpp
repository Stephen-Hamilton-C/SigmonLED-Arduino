#include "commands/command.h"

Command::Command(LEDController* controller) {
    _controller = controller;
}
