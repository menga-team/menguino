#include <Arduino.h>

// datatypes
using byte = uint8_t;

// stm32 or arduino?
#if defined(ARDUINO_ARCH_STM32F0)
#define ar_res 4069
#else
#define ar_res 1024
#endif

// macros
#define dw digitalWrite
#define dr digitalRead
#define aw analogWrite
#define ar analogRead
#define pm pinMode
#define high(pin) digitalWrite(pin, HIGH)
#define low(pin) digitalWrite(pin, LOW)
#define menga_pinmap(pin, min, max) map(analogRead(pin), 0, ar_res-1, min, max)
#define menga_pwm(in, out) aw(out, menga_pinmap(in, 0, 255))
#define menga_pwm_inverse(in, out) aw(out, menga_pinmap(in, 255, 0))
#define print(message) Serial.println(message)

class MengaLED {
private:
    byte _pin;
    byte _value;
    bool _high_side;
    void write();
public:
    MengaLED(byte pin, byte initial_value = 0, bool high_side = true);
    void on();
    void off();
    void set(byte value);
    void toggle();
    void pwm_pin(byte input_pin);
    void pwm_value(byte input_value);
    byte get();
};

class MengaButton {
private:
    byte _pin;
    int _debounce;
    bool _toggle;
    bool _on;
    byte _status;
    byte _last_value;
    unsigned long _last_millis;
    bool _debounce_update(byte value);
public:
    MengaButton(byte pin, bool toggle = false, int debounce_milliseconds = 10, bool high_side = true);
    bool update();
    byte get();
};

class MengaClock {
private:
    int _interval;
    unsigned long _last_tick;
    bool _run;
public:
    MengaClock(int interval = 500);
    bool tick();
    void set(int interval);
    void set_interval(int interval);
    void set_frequency(int frequency);
    void stop();
    void resume();
    void restart();
};

class MengaBuzzer {
private:
    MengaClock *_clock;
    MengaLED *_buzzer;
public:
    MengaBuzzer(byte pin, byte initial_value = 0, int frequency = 440);
    void update();
    void set_frequency(int frequency);
    void stop();
    void resume();
};
