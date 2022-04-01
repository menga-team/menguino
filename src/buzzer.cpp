#include "../include/menguino.h"

MengaBuzzer::MengaBuzzer(byte pin, byte initial_value, int frequency) {
    _clock = new MengaClock();
    _clock->set_frequency(frequency);
    _buzzer = new MengaLED(pin);
    _buzzer->set(initial_value);
}
void MengaBuzzer::update() {
    if (_clock->tick()) {_buzzer->off(); _buzzer->on();}
}
void MengaBuzzer::set_frequency(int frequency) {_clock->set_frequency(frequency);}
void MengaBuzzer::stop() {_clock->stop();}
void MengaBuzzer::resume() {_clock->resume();}
