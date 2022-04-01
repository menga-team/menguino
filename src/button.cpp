#include "../include/menguino.h"

bool MengaButton::_debounce_update(byte value) {
    if (_toggle) {
        if (_last_value == !_on && value == _on) {
            _status = !_status;
            return true;
        }
        return false;
    }
    else {
        if (_on) _status = value;
        else _status = !value;
        return true;
    }
}
MengaButton::MengaButton(byte pin, bool toggle, int debounce_milliseconds, bool high_side) {
    _status = 0;
    _last_value = 0;
    _last_millis = 0;
    _pin = pin;
    _debounce = debounce_milliseconds;
    _toggle = toggle;
    _on = high_side;
    _status = !_on;
    pm(_pin, INPUT);
}
bool MengaButton::update() {
    bool triggered = false;
    byte value = dr(_pin);
    if (value != _last_value) { // change since last update, but may be contact bounce
        if (millis() > _last_millis + _debounce) { // debounce_milliseconds have passed, it's not contact bounce
            _last_millis = millis();
            triggered =  _debounce_update(value);
        }
        else Serial.println("unwanted");
        _last_value = value;
    }
    return triggered;
}
byte MengaButton::get() {return _status;}