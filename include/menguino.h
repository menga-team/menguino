#ifndef MENGUINO_H
#define MENGUINO_H

#include <Arduino.h>
#include <stdint.h>

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

// flags
#define EVENTBASED 0
#define BUFFERBASED 1

void serial_init();

//bool _menguino_debug = false;
//void debug_init() {_menguino_debug = true;}
//void dbprint(char* message) {if (_menguino_debug) {_menguino_init_serial(); Serial.println(message);}}

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

class MengaSerial {
private:
    int _baud;
    byte* _id_value;
    byte* _id_value_reversed;
    byte _id_length;
    byte _mode;
public:
    /// create serial interface, providing baud and identifier
    MengaSerial(int baud = 9600, byte id_length = 2, byte* id_value = nullptr);

    /// initialize serial communication and select mode
    void init(byte mode = EVENTBASED);

    /// send null-terminated char array pre- and suffixed with identifier
    void send(char* message);

    /// in event mode, set function triggered by message
    void create_event(*char message, std::function<void()>);

    /// in buffer mode, true if message(s) are available to read
    bool available();

    /// in buffer mode, returns null-terminated char array of the oldest message in buffer
    char* read();

    ~MengaSerial();
};

#endif