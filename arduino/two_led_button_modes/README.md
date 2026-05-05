# Two LED Button Modes

Platform: Arduino Uno / ATmega328P

## Features

- Direct register access using DDRB, PORTB, PINB
- Two LEDs controlled through struct-based driver
- Button input using internal pull-up
- Falling-edge detection
- Time-based debounce
- Non-blocking blinking using millis()
- Modes:
  - OFF
  - BLINKING
  - FAST_BLINKING

## Hardware

- LED1: Arduino pin 13 / PB5
- LED2: Arduino pin 12 / PB4
- Button: Arduino pin 8 / PB0
- Button wired to GND using internal pull-up
