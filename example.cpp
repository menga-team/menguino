#include "menguino.h"

MengaLED led(PA3);
MengaLED blink(PA5);
MengaButton button(PA4, true);
MengaClock clock(1000);

void setup() {
    button.setup();
    led.setup();
    blink.setup();
}

void loop() {
    if (button.update()) led.toggle();
    if (clock.tick()) blink.toggle();
}