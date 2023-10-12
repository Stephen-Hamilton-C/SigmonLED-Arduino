#include "commandhandler.h"

void CommandHandler::loop() {
    _controller.loop();
}

void CommandHandler::execute(char** arguments, int argCount) {
    for(int i = 0; i < COMMAND_COUNT; i++) {
        char name[NAME_LEN] = {};
        _commands[i]->getName(name);
        if(strcmp(arguments[0], name) == 0) {
            _commands[i]->run(arguments, _controller);
        }
    }
}

int CommandHandler::getArgCount(char cmdName[]) {
    for(int i = 0; i < COMMAND_COUNT; i++) {
        char name[NAME_LEN] = {};
        _commands[i]->getName(name);
        if(strstr(cmdName, name) != NULL) {
            return _commands[i]->getArgCount() + 1;
        }
    }

    return -1;
}
