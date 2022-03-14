#include <Arduino.h>

// datatypes
using byte = unsigned char;

// macros
int power(int x, unsigned int p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    int tmp = power(x, p/2);
    if (p%2 == 0) return tmp * tmp;
    else return x * tmp * tmp;}
#define ar_res 12 // analogReadResolution; 12 for STM32, 10 for Arduino Uno; TODO: determine this automatically
#define dw digitalWrite
#define dr digitalRead
#define aw analogWrite
#define ar analogRead
#define pm pinMode
#define high(pin) digitalWrite(pin, HIGH)
#define low(pin) digitalWrite(pin, LOW)
#define menga_pinmap(pin, min, max) map(analogRead(pin), 0, power(2, ar_res)-1, min, max)
#define menga_pwm(in, out) aw(out, menga_pinmap(in, 0, 255))
#define menga_pwm_inverse(in, out) aw(out, menga_pinmap(in, 255, 0))
#define print(message) Serial.println(message)

// Apparently Arduino needs this function to run properly.
// it is defined here, so you don't have to put it in your code.
// if you need it though, just overwrite ours.
void setup() {Serial.begin(9600);}

class MengaLED {
private:
    byte _pin;
    byte _value;
    void write() {dw(_pin, _value);}
public:
    MengaLED(byte pin, byte initial_value = 0) {
        _pin = pin;
        _value = initial_value;
        pm(_pin, OUTPUT);
    }
    void on() {_value = 1; write();}
    void off() {_value = 0; write();}
    void set(byte value) {_value = value; write();}
    void toggle() {_value = !_value; write();}
    void pwm_pin(byte input_pin) {menga_pwm(input_pin, _pin);}
    void pwm_value(byte input_value) {aw(_pin, input_value);}
};

class MengaButton {
private:
    byte _pin;
    int _debounce;
    bool _toggle;
    byte _status = 0;
    byte _last_value = 0;
    unsigned long _last_millis = 0;
    bool _debounce_update(byte value) {
        if (_toggle) {
            if (_last_value == 0 && value == 1) {
                _status = !_status;
                return true;
            }
            return false;
        }
        else {
            _status = value;
            return true;
        }
    }
public:
    MengaButton(byte pin, bool toggle = false, int debounce_milliseconds = 10) {
        _pin = pin;
        _debounce = debounce_milliseconds;
        _toggle = toggle;
        pm(_pin, INPUT);
    }
    bool update() {
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
};

class MengaClock {
private:
    int _interval;
    unsigned long _last_tick = 0;
public:
    MengaClock(int interval = 500) {
        _interval = interval;
    }
    bool tick() {
        if (millis() > _last_tick + _interval) {
            _last_tick = millis();
            return true;
        }
        return false;
    }
};