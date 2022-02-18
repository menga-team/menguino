#include <Arduino.h>

using byte = unsigned char;

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

class MengaLED {
private:
    byte _pin;
    byte _value;
    void write() {dw(_pin, _value);}
public:
    MengaLED(byte pin, byte initial_value = 0) {
        _pin = pin;
        _value = initial_value;
    }
    void setup() {pm(_pin, OUTPUT);}
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
    byte _debounce;
    bool _toggle;
    byte _status = 0;
    byte _last_value = 0;
    unsigned long _last_millis = 0;
public:
    MengaButton(byte pin, bool toggle = false, byte debounce_milliseconds = 10) {
        _pin = pin;
        _debounce = debounce_milliseconds;
        _toggle = toggle;
    }
    void setup() {pm(_pin, INPUT);}
    bool update() {
        bool toggled = false;
        byte value = dr(_pin);
        if (value != _last_value) {
            if (millis() > _last_millis + _debounce) {
                if (_toggle) {
                    if (_last_value == 0 && value == 1) {
                        _status = !_status;
                        toggled = true;
                    }
                }
                else {
                    _status = value;
                    toggled = true;
                }
                _last_millis = millis();
                _last_value = value;
            }
        }
        return toggled;
    }
    byte get() {return _status;}
};