# menguino
A general purpose Arduino Framework Library, worse than the competition,
but all the Classes start with "Menga" so that's pretty cool.

## Installation
To include the library into PlatformIO, simply add the following line to your `platformio.ini`.
```
lib_deps = 
    https://github.com/menga-team/menguino.git
```
To test if everything works, try one of the examples located in the [examples folder](examples/).

## Development
To test the library locally, consider using a script like the following:
```
#!/bin/bash
pio pkg uninstall --library <path to menguino>
pio pkg install --library <path to menguino>
pio run --target upload
```

# Documentation
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
Menguino also provides `MengaClock`, which can be used as a stopwatch [todo]
or as a simple clock to trigger events continuously at a given frequency.

### MengaClock
- `int interval = 500` _Tick interval in milliseconds_


- `tick()` returns true if the clock ticked.

## Communication
By enabling serial debugging using the `debug_init()` function, menguino provides `dbprint(char* message)`,
which simply sends the contents of the null-terminated char array out of the serial bus,
just like `Serial.println()` would. Additionally, menguino classes will print out some debug info if
debugging is enabled.

To simplify communication, menguino provides `MengaSerial`. Using this class messages pre- and
suffixed with an id can be sent and received [todo] to avoid misinterpretations when the
communication gets interrupted or starts in the middle of a message.

### MengaSerial
- `void init(byte mode)` initialize serial communication and select mode
- `void send(char* message)` send null-terminated char array pre- and suffixed with identifier
- `void create_event(*char message, std::function<void()>)` in event mode, set function triggered by message
- `bool available()` in buffer mode, true if message(s) are available to read
- `char* read()` in buffer mode, returns null-terminated char array of the oldest message in buffer