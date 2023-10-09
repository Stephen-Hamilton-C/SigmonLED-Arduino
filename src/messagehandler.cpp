#include "messagehandler.h"

// Public
void MessageHandler::loop() {
    if (_currentState == State::ACKNOWLEDGE) {
        if(millis() - _lastMessageTimestamp >= MESSAGE_TIMEOUT) {
            _currentState = State::RECEIVE;
            Serial.println(RESPONSE_DISREGARD);
            _cleanup();
        }
    }
}

void MessageHandler::processMessage(char message[], int messageLen) {
    switch(_currentState) {
        case State::RECEIVE: {
            _currentMessage = _splitCommand(message, messageLen);
            if(_currentMessage == NULL) {
                // Invalid command
                Serial.println(RESPONSE_DISREGARD);
                return;
            }

            Serial.print(RESPONSE_VERIFY);
            for(int i = 0; i < _currentArgCount; i++) {
                Serial.print(_currentMessage[i]);
                if(i < _currentArgCount - 1) {
                    Serial.print(' ');
                }
            }
            Serial.print('\n');
            _lastMessageTimestamp = millis();
            _currentState = State::ACKNOWLEDGE;
            break;
        }
        case State::ACKNOWLEDGE: {
            _currentState = State::RECEIVE;
            if(strstr(message, MESSAGE_CONFIRM) != NULL) {
                // Execute command based on _currentMessage[0]
                Serial.println(RESPONSE_CONFIRM);
                _commandHandler.execute(_currentMessage, _currentArgCount);
            } else {
                processMessage(message, messageLen);
                return;
            }
            _cleanup();
            break;
        }
    }
}

// Private
char** MessageHandler::_splitCommand(char message[], int messageLen) {
    if(strstr(message, "command") != NULL) {
        _currentArgCount = 3;
    } else {
        return NULL;
    }

    char** arguments = new char*[_currentArgCount];
    for(int i = 0; i < _currentArgCount; i++) {
        arguments[i] = NULL;
    }

    char argBuffer[MESSAGE_BUFFER / 2];
    int argBufferLen = 0;

    int arg = 0;
    for(int i = 0; i < messageLen; i++) {
        if(argBufferLen >= (MESSAGE_BUFFER / 2) - 1) {
            _freeStringArray(arguments, _currentArgCount);
            return NULL;
        }

        if(message[i] == ' ' || message[i] == '\n') {
            argBuffer[argBufferLen++] = '\0';
            arguments[arg] = new char[argBufferLen];
            strcpy(arguments[arg++], argBuffer);
            argBufferLen = 0;

            // Sufficient arguments. Ignore the rest of the message
            if(arg >= _currentArgCount) {
                break;
            }
        } else {
            argBuffer[argBufferLen++] = message[i];
        }
    }

    for(int i = 0; i < _currentArgCount; i++) {
        if(arguments[i] == NULL) {
            // Found an argument that was not supplied
            _freeStringArray(arguments, _currentArgCount);
            return NULL;
        }
    }

    return arguments;
}

void MessageHandler::_cleanup() {
    _freeStringArray(_currentMessage, _currentArgCount);
    _currentMessage = NULL;
    _currentArgCount = 0;
    _lastMessageTimestamp = 0;
}

void MessageHandler::_freeStringArray(char** str, int len) {
    for(int i = 0; i < len; i++) {
        delete str[i];
    }

    delete str;
}
