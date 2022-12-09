#include <Arduino.h>
#include "../include/menguino.h"


MengaClock::MengaClock(int interval) {
    _last_tick = 0;
    _run = true;
    _interval = interval;
}
bool MengaClock::tick() {
    if (_run && millis() > _last_tick + _interval) {
        _last_tick = millis();
        return true;
    }
    return false;
}
void MengaClock::set(int interval) {_interval = interval;}
void MengaClock::set_interval(int interval) {set(interval);}
void MengaClock::set_frequency(int frequency) {_interval = 1000/frequency;}
void MengaClock::stop() {_run = false;}
void MengaClock::resume() {_run = true;}
void MengaClock::restart() {_last_tick = millis();}