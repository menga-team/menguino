#include "menguino.h"

MengaLED led(PB3);
MengaButton button(PB4, true);

void setup() {}

void loop() {
    if (button.update()) led.toggle();
}