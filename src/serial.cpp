#include <Arduino.h>
#include "../include/menguino.h"
#include <string.h>

void serial_init() { Serial.begin(BAUD); while (!Serial) ;}

MengaSerial::MengaSerial(byte id_length, byte* id_value) {
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

