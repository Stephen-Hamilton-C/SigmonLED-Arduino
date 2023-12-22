#include "config.h"

#if ENABLE_SERIAL_COMMANDS
#include "messagehandler.h"

#include "commands.h"

// Public
MessageHandler::MessageHandler(LEDController* controller) {
    _controller = controller;
}

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
            for(int i = 0; i < _currentInfo.argCount; i++) {
                Serial.print(_currentMessage[i]);
                if(i < _currentInfo.argCount - 1) {
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
                _currentInfo.command->run(_currentMessage, _controller);
                _cleanup();
            } else {
                _cleanup();
                processMessage(message, messageLen);
                return;
            }
            break;
        }
    }
}

// Private
char** MessageHandler::_splitCommand(char message[], int messageLen) {
    _currentInfo = Commands::getArgCount(message);
    if(_currentInfo.argCount <= 0) {
        return NULL;
    }

    char** arguments = new char*[_currentInfo.argCount];
    for(int i = 0; i < _currentInfo.argCount; i++) {
        arguments[i] = NULL;
    }

    char argBuffer[MESSAGE_BUFFER / 2];
    int argBufferLen = 0;

    int arg = 0;
    for(int i = 0; i < messageLen; i++) {
        if(argBufferLen >= (MESSAGE_BUFFER / 2) - 1) {
            _cleanup();
            return NULL;
        }

        if(message[i] == ' ' || message[i] == '\n') {
            argBuffer[argBufferLen++] = '\0';
            arguments[arg] = new char[argBufferLen];
            strcpy(arguments[arg++], argBuffer);
            argBufferLen = 0;

            // Sufficient arguments. Ignore the rest of the message
            if(arg >= _currentInfo.argCount) {
                break;
            }
        } else {
            argBuffer[argBufferLen++] = message[i];
        }
    }

    for(int i = 0; i < _currentInfo.argCount; i++) {
        if(arguments[i] == NULL) {
            // Found an argument that was not supplied
            _cleanup();
            return NULL;
        }
    }

    return arguments;
}

void MessageHandler::_cleanup() {
    _freeStringArray(_currentMessage, _currentInfo.argCount);
    _currentMessage = NULL;
    _lastMessageTimestamp = 0;
    delete _currentInfo.command;
    _currentInfo = CommandInfo {
        argCount: -1,
        command: nullptr
    };
}

void MessageHandler::_freeStringArray(char** str, int len) {
    for(int i = 0; i < len; i++) {
        delete str[i];
    }

    delete str;
}
#endif
