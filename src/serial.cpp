#include <Arduino.h>
#include "../include/menguino.h"
#include <string.h>

MengaSerial::MengaSerial(int baud, byte id_length, byte* id_value) {
    _baud = baud;
    _id_length = id_length;
    if (_id_length > 8) {
        _id_length = 8;
        //dbprint("MengaSerial::MengaSerial() -> truncating serial id to 8 bytes");
    }
    _id_value = (byte*) malloc(_id_length);
    if (id_value == nullptr) {
        for (int i = 0; i < _id_length; i++) {
            _id_value[i] = 248+i;
        }
    }
    else {
        memcpy(_id_value, id_value, _id_length);
    }
    _id_value_reversed = (byte*) malloc(_id_length);
    for (int i = 0; i < _id_length; i++) {
        _id_value_reversed[_id_length-i-1] = _id_value[i];
    }
    //dbprint("MengaSerial::MengaSerial() -> serial interface successfully created");
}

void MengaSerial::send(char *message) {
    Serial.write(_id_value, _id_length);
    Serial.write(message, strlen(message));
    Serial.write(_id_value_reversed, _id_length);
}

void MengaSerial::init(byte mode) {
    _mode = mode;
    Serial.begin(_baud);
    while (!Serial);
}

void MengaSerial::create_event(*char message, std::function<void()>) {
    if (_mode != EVENTBASED) return;
    // WIP
}

bool MengaSerial::available() {
    if (_mode != BUFFERBASED) return;
    // WIP
}

void MengaSerial::read() {
    if (_mode != BUFFERBASED) return;
    // WIP
}