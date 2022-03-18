#include "menguino.h"

MengaLED led(PB3);
MengaClock clock(500);

void setup() {}

void loop() {
    if (clock.tick()) led.toggle();
}