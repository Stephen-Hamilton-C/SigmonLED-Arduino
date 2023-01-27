#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <stdint.h>
#include "ledcontroller.h"

class CommandHandler {
public:
    CommandHandler(LEDController* controller);
    void handle(const uint8_t* readBuffer[], uint8_t& len);

private:
    LEDController* _controller;
};

#endif
