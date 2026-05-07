# EmbeddedLearningStuff

Personal embedded systems learning repository.

---

## 🎯 Focus

- C fundamentals
- Register-level programming
- GPIO control
- Bit manipulation
- Interrupt-driven systems
- Hardware timers
- Non-blocking timing
- Button input handling
- Software debounce
- Struct-based drivers
- Function pointers and callback systems
- Embedded architecture patterns
- Multi-file embedded project organization
- Preparation for STM32 and later ESP32

---

## 📚 Concepts Practiced

### 🔧 Low-Level Hardware Control

- Direct register manipulation
- GPIO configuration using:
  - `DDRx`
  - `PORTx`
  - `PINx`
- Bit masking and bitwise operations

---

### ⚡ Interrupts & Timing

- External interrupts (`INT0`)
- Timer compare interrupts
- Timer1 CTC (Clear Timer on Compare) mode
- ISR (Interrupt Service Routine) design
- Event-driven programming

---

### ⏱️ Non-Blocking Design

- Replacing `delay()` with timing logic
- `millis()`-based scheduling
- Hardware timer-driven scheduling

---

### 🔘 Input Handling

- Internal pull-up resistors
- Active-low button logic
- Edge detection
- Timer-based debounce

---

### 🔒 Concurrency & Safety

- `volatile`
- Race conditions
- Atomic operations
- `ATOMIC_BLOCK`

---

### 🧱 Embedded Software Design

- Struct-based drivers
- Pointer-based APIs
- Generic callback systems
- Function pointers + context pointers (`void *`)
- Module separation and ownership

---

## 📂 Projects

### Arduino

#### `two_led_button_modes`

Arduino Uno project demonstrating:

- Register-level GPIO control
- Two independent LEDs
- Debounced button input
- Non-blocking timing
- Enum-based finite state machine
- Struct-based driver architecture

---

#### `interrupt_driven_button_debounce`

Arduino Uno project demonstrating:

- External interrupts using `INT0`
- Timer1 compare match interrupts
- Hardware timer-based debounce
- Generic callback architecture
- Atomic shared-state protection
- Struct-based embedded drivers
- PlatformIO-based embedded workflow

---

## 🚀 Learning Path

Current direction:

```text
Arduino Register-Level Programming
            ↓
Interrupts & Timers
            ↓
Embedded Architecture Patterns
            ↓
STM32
            ↓
ESP32
```

---

## 📌 Note

This repository intentionally avoids heavy framework abstractions.

The goal is to build:
- hardware understanding
- timing awareness
- embedded debugging skills
- portable embedded design habits

that transfer cleanly to professional MCU platforms.
# PS
*ALL README files shamelessly generated via LLM :D*
