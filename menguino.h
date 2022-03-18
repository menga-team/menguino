#include <Arduino.h>

// datatypes
using byte = unsigned char;

// cool power function
int power(int x, unsigned int p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    int tmp = power(x, p/2);
    if (p%2 == 0) return tmp * tmp;
    else return x * tmp * tmp;}

// stm32 or arduino?
#if defined(ARDUINO_ARCH_STM32F0)
#define ar_res 12
#else
#define ar_res 10
#endif

// macros
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

class MengaLED {
private:
    byte _pin;
    byte _value;
    bool _high_side;
    void write() {
        if (_high_side) dw(_pin, _value);
        else dw(_pin, !_value);
    }
public:
    MengaLED(byte pin, byte initial_value = 0, bool high_side = true) {
        _pin = pin;
        _value = initial_value;
        _high_side = high_side;
        pm(_pin, OUTPUT);
    }
    void on() {_value = 1; write();}
    void off() {_value = 0; write();}
    void set(byte value) {_value = value; write();}
    void toggle() {_value = !_value; write();}
    void pwm_pin(byte input_pin) {menga_pwm(input_pin, _pin);}
    void pwm_value(byte input_value) {aw(_pin, input_value);}
    byte get() {return _value;}
};

class MengaButton {
private:
    byte _pin;
    int _debounce;
    bool _toggle;
    bool _on;
    byte _status = 0;
    byte _last_value = 0;
    unsigned long _last_millis = 0;
    bool _debounce_update(byte value) {
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
public:
    MengaButton(byte pin, bool toggle = false, int debounce_milliseconds = 10, bool high_side = true) {
        _pin = pin;
        _debounce = debounce_milliseconds;
        _toggle = toggle;
        _on = high_side;
        _status = !_on;
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
    byte get() {return _status;}
};

class MengaClock {
private:
    int _interval;
    unsigned long _last_tick = 0;
    bool _run = true;
public:
    MengaClock(int interval = 500) {
        _interval = interval;
    }
    bool tick() {
        if (_run && millis() > _last_tick + _interval) {
            _last_tick = millis();
            return true;
        }
        return false;
    }
    void set(int interval) {_interval = interval;}
    void set_interval(int interval) {set(interval);}
    void set_frequency(int frequency) {_interval = 1000/frequency;}
    void stop() {_run = false;}
    void resume() {_run = true;}
    void restart() {_last_tick = millis();}
};