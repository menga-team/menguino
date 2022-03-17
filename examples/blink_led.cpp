#include "menguino.h"

MengaLED led(PB3);
MengaClock clock(500);

void loop() {
    if (clock.tick()) blink.toggle();
}