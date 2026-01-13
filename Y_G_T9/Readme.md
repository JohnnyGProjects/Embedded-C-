# 🔢 Seven-Segment Counter with Interrupts (Arduino / AVR)

This project implements a **seven-segment display counter** using an **Arduino-compatible AVR microcontroller**, controlled through **pin-change interrupts (PCINT)**, **Timer1 overflow interrupts**, and a **74HC595 shift register**.  
The system demonstrates low-level hardware control, interrupt-driven logic, and direct register manipulation without relying on Arduino abstraction libraries.

---

## 🧩 Module Overview

### ⚙️ `main.cpp`

* Entry point of the application
* Initializes shift register, interrupts, and Timer1
* Controls counter state and display logic
* Implements:
  * Forward counting (0 → 9)
  * Reverse counting (9 → 0)
  * Stop state
* Contains ISR implementations for:
  * `PCINT0_vect`
  * `TIMER1_OVF_vect`

---

### 🔘 `PCINT0.h / PCINT0.cpp`

* Defines button inputs using **Pin Change Interrupts**
* Configures:
  * `PCINT0` and `PCINT1` for button detection
  * Internal pull-up resistors
* Initializes **Timer1** with a prescaler and overflow interrupt
* Enables global interrupts using `sei()`

---

### 🔢 `Segment.h / Segment.cpp`

* Manages seven-segment display output
* Converts numeric values into segment byte patterns
* Sends data to the shift register using a latch-based update mechanism

---

### 🔄 `ShiftReg.h / ShiftReg.cpp`

* Controls a **74HC595 shift register**
* Configures data, clock, and latch pins
* Implements a custom `myShiftOut()` function
* Supports:
  * Least Significant Bit first (LSBFIRST)
  * Direct PORT manipulation for timing accuracy

---

## ⚙️ Core Functionality

* Displays digits **0–9** on a seven-segment display
* Uses **Timer1 overflow interrupts** to control counting speed
* Uses **Pin Change Interrupts** to control counter state:
  * Button 1 → Stop counting
  * Button 2 → Reverse counting direction
* Implements modulo-based counting logic
* Uses direct register access (`PORTx`, `DDRx`, `PINx`) for hardware control

---

## 🧠 Embedded Systems Concepts Demonstrated

* AVR register-level programming
* Pin Change Interrupts (PCINT)
* Timer1 configuration and overflow handling
* Interrupt Service Routines (ISR)
* Shift register communication
* Bitwise operations and masking
* Volatile variables for interrupt safety
* Hardware debouncing via state tracking

---

## 🛠️ Technologies Used

* C / C++
* Arduino framework (minimal abstraction)
* AVR libraries
* ATmega microcontroller architecture
* 74HC595 shift register
* Seven-segment display

---

## ▶️ How It Works (High Level)

1. Timer1 triggers periodic overflow interrupts
2. Each overflow updates the counter value
3. Counter value is mapped to a seven-segment byte pattern
4. Pattern is sent serially to the shift register
5. Button presses trigger pin-change interrupts that modify counter state

---

## 🎯 Project Purpose

This project was created to:

* Demonstrate low-level embedded programming skills
* Practice interrupt-driven system design
* Control external hardware using shift registers
* Apply AVR timer and interrupt concepts
* Reinforce register-level programming without Arduino abstractions

---

## 👨‍💻 Author

**Johnny (Yoseph Gebre)**  
IT Graduate — Carleton University  
Interest in embedded systems, and hardware-software integration

---

## 📄 License

This project is for educational and portfolio purposes.
