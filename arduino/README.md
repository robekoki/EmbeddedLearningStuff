# Arduino Experiments

This directory contains hands-on projects built on Arduino Uno (ATmega328P) while learning embedded systems fundamentals.

The focus is on **low-level, register-based programming**, not Arduino abstractions.

---

## 🎯 Purpose

* Transition from high-level development → embedded systems
* Build strong understanding of:

  * GPIO registers (DDRx, PORTx, PINx)
  * Bit manipulation
  * Timing without blocking
  * Hardware interaction
* Prepare for working with MCUs like STM32

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
```

This gives full control over hardware behavior and timing.

---

## 📚 Concepts Practiced

### 🔧 GPIO Control

* Setting pin direction via `DDRB`
* Writing outputs via `PORTB`
* Reading inputs via `PINB`

---

### 🔁 Bit Manipulation

* Setting, clearing, toggling bits
* Using masks to control specific pins

---

### ⏱️ Non-blocking Timing

* Replacing `delay()` with time comparison
* Using `millis()` safely (overflow-aware)

---

### 🔘 Button Input

* Internal pull-up resistors
* Active-low logic
* Edge detection (press events)
* Software debounce

---

### 🧱 Driver Design

* Struct-based LED driver
* Struct-based Button driver
* Pointer-based APIs (`LED*`, `Button*`)

---

### 🔄 Finite State Machines

* Mode switching using enum-based FSM
* Behavior driven by state instead of conditions

---

## 📂 Projects

### `two_led_button_modes`

A small embedded system demonstrating:

* Two LEDs with independent blinking intervals
* Button-controlled mode switching
* Debounced input handling
* Non-blocking timing
* Struct-based driver architecture

---

## 🧠 Key Takeaways

* Hardware must be controlled explicitly
* Time must be managed manually (no scheduler)
* Non-blocking design is essential
* Structs help model real devices
* Code should separate:

  * hardware access
  * logic
  * state

---

## 🚀 Next Steps

* External interrupts (button via ISR)
* Hardware timers (replace `millis()`)
* Multi-file project structure (`.c/.h`)
* Transition to STM32

---

## 📌 Note

Arduino is used here as a **learning platform**, not as a framework.
The goal is to write code that can be easily ported to other microcontrollers.
