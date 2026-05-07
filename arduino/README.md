# Arduino Experiments

This directory contains hands-on projects built on Arduino Uno (ATmega328P) while learning embedded systems fundamentals.

The focus is on **low-level, register-based programming**, not Arduino abstractions.

---

## 🎯 Purpose

- Transition from high-level development → embedded systems
- Build strong understanding of:
  - GPIO registers (`DDRx`, `PORTx`, `PINx`)
  - Bit manipulation
  - Interrupt-driven systems
  - Hardware timers
  - Non-blocking design
  - Hardware interaction
  - Embedded architecture patterns
- Prepare for working with MCUs like STM32

---

## ⚙️ Approach

Instead of using Arduino functions like:

```cpp
digitalWrite(pin, HIGH);
delay(1000);
```

I use:

```c
PORTB |= (1 << 5);

if ((now - last_time) >= interval)
{
    // execute task
}
```

or direct hardware configuration:

```c
EIMSK |= (1 << INT0);
TCCR1B |= (1 << WGM12);
```

This gives full control over:
- hardware behavior
- timing
- interrupts
- event handling

---

## 📚 Concepts Practiced

### 🔧 GPIO Control

- Setting pin direction via `DDRx`
- Writing outputs via `PORTx`
- Reading inputs via `PINx`

---

### 🔁 Bit Manipulation

- Setting, clearing, toggling bits
- Using masks to control specific pins

---

### ⏱️ Non-blocking Timing

- Replacing `delay()` with time comparison
- Using `millis()` safely (overflow-aware)
- Hardware timer-based scheduling using Timer1

---

### ⚡ Interrupts

- External interrupts using `INT0`
- Interrupt flags and masks
- ISR (Interrupt Service Routine) design
- Event-driven programming

---

### 🔘 Button Input

- Internal pull-up resistors
- Active-low logic
- Edge detection (press events)
- Software debounce
- Timer-based debounce using interrupts

---

### 🔒 Concurrency & Safety

- `volatile`
- Atomic operations
- Race conditions
- `ATOMIC_BLOCK`

---

### 🧱 Driver Design

- Struct-based LED driver
- Struct-based Button driver
- Pointer-based APIs (`LED*`, `Button*`)
- Generic callback systems
- Function pointers + context pointers (`void *`)

---

### 🔄 Finite State Machines

- Mode switching using enum-based FSM
- Behavior driven by state instead of nested conditions

---

### 📂 Multi-file Embedded Projects

- `.c/.h` project organization
- Separation of:
  - drivers
  - application logic
  - hardware abstraction
- PlatformIO workflow

---

## 📂 Projects

### `two_led_button_modes`

A small embedded system demonstrating:

- Two LEDs with independent blinking intervals
- Button-controlled mode switching
- Debounced input handling
- Non-blocking timing
- Struct-based driver architecture
- Enum-based finite state machine

---

### `interrupt_driven_button_debounce`

An interrupt-driven embedded application demonstrating:

- External interrupts using `INT0`
- Timer1 compare match interrupts
- Hardware timer-based debounce
- Generic timer callback architecture
- Atomic shared-state protection
- Struct-based driver architecture
- PlatformIO-based embedded workflow

---

## 🧠 Key Takeaways

- Hardware must be controlled explicitly
- Time must be managed manually
- Interrupts create concurrent execution contexts
- Non-blocking design is essential
- Structs help model real devices
- Generic callbacks reduce module coupling
- Atomic protection is required for shared ISR/main state
- Code should separate:
  - hardware access
  - timing
  - event generation
  - application logic

---

## 🚀 Next Steps

- Multiple button/interrupt support
- Generic external interrupt manager
- Event queues
- Cooperative scheduler
- STM32 transition
- UART communication
- SPI/I2C peripherals
- RTOS concepts

---

## 📌 Note

Arduino is used here as a **learning platform**, not as a framework.

The goal is to write code that can be:
- portable
- hardware-aware
- scalable
- easily transitioned to STM32 and other MCUs.
