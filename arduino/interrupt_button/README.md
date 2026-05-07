# Interrupt-Driven Button Debounce
Platform: Arduino Uno / ATmega328P

---

## Features

- Direct register access using:
  - `DDRB`, `PORTB`, `PIND`
  - `EICRA`, `EIMSK`, `EIFR`
  - `TCCR1A`, `TCCR1B`, `OCR1A`, `TIMSK1`

- External interrupt-driven button handling using `INT0`
- Hardware timer-based debounce using Timer1 in CTC (**C**lear **T**imer on **C**ompare) mode
- 1 ms system tick generated from Timer1 compare match interrupt
- Struct-based Button and LED drivers
- Multi-file embedded project structure (`.c/.h`)
- PlatformIO-based workflow
- Generic timer callback architecture using:
  - Function pointers
  - Context pointers (`void *`)
- Atomic shared-state protection using:
  - `volatile`
  - `ATOMIC_BLOCK`
- Event-driven application flow
- Non-blocking design (no `delay()`)

---

## Architecture

### Timer Module

- Configures Timer1 for:
  - CTC mode
  - Prescaler 64
  - `OCR1A = 249`

- Generates interrupt every 1 ms
- Executes registered callback through generic callback system

### Button Module

- Uses `INT0` (**INT**errupt 0) on falling edge
- Starts debounce window on interrupt
- Disables `INT0` during debounce period
- Confirms button state after debounce timeout
- Generates clean press events

### LED Module

- Simple GPIO (**G**eneral **P**urpose **I**nput/**O**utput) output abstraction
- Struct-based LED control

---

## Interrupt Flow

```text
Button press
    ↓
INT0 ISR
    ↓
Button_handleInterrupt()
    ↓
Debounce started
    ↓
Timer1 ISR every 1 ms
    ↓
Registered callback executes
    ↓
Button_tick_1ms()
    ↓
Debounce confirmed
    ↓
pressed_event set
    ↓
Main loop consumes event
    ↓
LED toggles
```

---

## Hardware

- LED: Arduino pin 13 / PB5
- Button: Arduino pin 2 / PD2 / INT0
- Button wired to GND using internal pull-up

---

## Concepts Learned

- Polling vs interrupt-driven systems
- Hardware interrupt architecture
- Timer compare interrupts
- Debounce using hardware timers
- ISR (**I**nterrupt **S**ervice **R**outine) design rules
- `volatile` vs atomic access
- Race conditions
- Function pointers and callback systems
- Context-pointer callback architecture
- Module coupling and ownership
- Embedded project organization using PlatformIO