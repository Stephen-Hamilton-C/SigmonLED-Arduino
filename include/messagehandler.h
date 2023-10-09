#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "config.h"
#include "commandhandler.h"
#include <Arduino.h>

#define RESPONSE_VERIFY "verify "
#define RESPONSE_CONFIRM "confirmed"
#define RESPONSE_DISREGARD "disregard"
#define MESSAGE_CONFIRM "confirm"

class MessageHandler {
public:
    void processMessage(char message[], int messageLen);
    void loop();

    enum State {
        RECEIVE,
        ACKNOWLEDGE
    };

private:
    char** _splitCommand(char message[], int messageLen);
    void _cleanup();
    void _freeStringArray(char** str, int len);

    CommandHandler _commandHandler;
    State _currentState = State::RECEIVE;
    char** _currentMessage = NULL;
    int _currentArgCount = 0;
    unsigned long _lastMessageTimestamp;
};

#endif
