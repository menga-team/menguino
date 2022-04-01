#include "../include/menguino.h"

void MengaLED::write() {
    if (_high_side) dw(_pin, _value);
    else dw(_pin, !_value);
}

MengaLED::MengaLED(byte pin, byte initial_value, bool high_side) {
    _pin = pin;
    _value = initial_value;
    _high_side = high_side;
    pm(_pin, OUTPUT);
    Serial.println("mengaled loaded"); // asdasdashdjhaskjdhaskjdhkjashd
}
void MengaLED::on() {_value = 1; write();}
void MengaLED::off() {_value = 0; write();}
void MengaLED::set(byte value) {_value = value; write();}
void MengaLED::toggle() {_value = !_value; write();}
void MengaLED::pwm_pin(byte input_pin) {menga_pwm(input_pin, _pin);}
void MengaLED::pwm_value(byte input_value) {aw(_pin, input_value);}
byte MengaLED::get() {return _value;}