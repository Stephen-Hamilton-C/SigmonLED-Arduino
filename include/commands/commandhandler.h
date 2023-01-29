#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <stdint.h>
#include "constants.h"
#include "ledcontroller.h"

class CommandHandler {
public:
    CommandHandler(LEDController& controller);
    void handle(const uint8_t (&readBuffer)[READ_BUFFER_SIZE], uint8_t& len);

private:
    LEDController& _controller;
};

#endif
