#include "/Users/emil/code/menga/menguino/menguino.h"

MengaClock clock;
int length = 8;
MengaLED leds[] = {PB3, PB4, PB5, PB6, PB8, PA2, PB0, PB1};

byte led_value(byte ledindex, byte value) {
    return ((value >> ledindex) & 1);
}

byte value = 0;
int millis_counter = 0;

void loop() {
    if (clock.tick()) {
        value++;
        for (int i = 0; i < length; i++) leds[i].set(led_value(i, value));
    }
}
