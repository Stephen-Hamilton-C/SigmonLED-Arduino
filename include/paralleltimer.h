#ifndef PARALLELTIMER_H
#define PARALLELTIMER_H

#include <Arduino.h>

typedef void(*TimerCallback)();

class ParallelTimer {
public:
    ParallelTimer(unsigned long milliseconds, TimerCallback callback);
    void loop();

private:
    unsigned long _start;
    unsigned long _target;
    TimerCallback _callback;
};

#endif
