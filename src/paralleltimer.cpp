#include "paralleltimer.h"

ParallelTimer::ParallelTimer(unsigned long milliseconds, TimerCallback callback) {
    _target = milliseconds;
    _callback = callback;
    _start = millis();
}

void ParallelTimer::loop() {
    if(millis() - _start >= _target) {
        _callback();
    }
}
