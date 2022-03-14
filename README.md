# menguino
An general purpose Arduino Framework Library, worse than the competition,
but the Classes all start with "Menga" so that's pretty cool.

## Components
Aside from various macros for I/O, menguino provides Classes to make it easier
for you to communicate with components in your circuit:

### MengaLED
- `byte pin` _The pin your LED is connected to_
- `byte initial_value = 0` _The LED's initial state is [off -> 0] [on -> 1]_
- `byte high_side = 1` _Led is connected [high-side -> 1] [low-side -> 0]_


- `void on()` turns LED on
- `void off()` turns LED off 
- `void set(byte value)` sets LED to specified value
- `void toggle()` toggles LED
- `void pwm_pin(byte input_pin)` connects pin with the LED's brightness (e.g. potentiometer)
- `void pwm_value(byte input_value)` sets the LED's brightness to specified pwm value

### MengaButton
- `byte pin` _The pin your Button is connected to_
- `bool toggle = false` _Should your Button be Toggled or Momentary_
- `byte debounce_milliseconds = 10` _Self explanatory_


- `update()` returns true if the button changed since the last update

## Timing
Menguino also provides MengaClock, which can be used as a stopwatch [todo]
or as a simple clock to trigger events continuously between a given interval.

### MengaClock
- `int interval = 500` _Tick interval in milliseconds_


- `tick()` returns true if the clock ticked.
