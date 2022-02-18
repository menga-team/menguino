#include "menguino.h"

MengaLED led(PA3);
MengaButton button(PA4, true);

void setup() {
    button.setup();
    led.setup();
}

void loop() {
    if (button.update()) led.toggle();
}