#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    virtual void run(char** command) = 0;
};

#endif
