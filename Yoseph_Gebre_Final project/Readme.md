# Embedded Systems Project – AVR Microcontroller

## Overview
This project is an AVR-based embedded systems application written in C/C++ using direct register manipulation. It integrates multiple hardware peripherals including an LCD, UART communication, push-button interrupts, timers, and a 7-segment display driven by a shift register.

All functionality is implemented at a low level using AVR registers rather than Arduino abstraction libraries.

---

## Features
- LCD control in 4-bit mode
- UART (USART) serial communication at 9600 baud
- Pin Change Interrupts (PCINT) for button input
- Timer1 overflow interrupts for periodic updates
- 7-segment display driven using a shift register
- User input via UART displayed on LCD
- Interrupt-driven counter logic

---

## Hardware Components
- AVR microcontroller (ATmega series)
- 16x2 LCD (4-bit mode)
- Push buttons (PCINT)
- 7-segment display
- Shift register (e.g., 74HC595)
- UART serial interface

---

## Pin Configuration

### LCD
| Signal | AVR Pin |
|------|--------|
| RS | PB1 |
| EN | PB0 |
| D4–D7 | PD4–PD7 |

### Shift Register
| Signal | AVR Pin |
|------|--------|
| DATA | PD4 |
| CLOCK | PD6 |
| LATCH | PD5 |

### Buttons
| Button | AVR Pin |
|-------|--------|
| Button 1 | PB0 |
| Button 2 | PB1 |

---

## Program Behavior
1. On startup, the system initializes:
   - USART
   - LCD
   - Shift register
   - Pin Change Interrupts
   - Timer1

2. The user is prompted over UART to enter their name.
3. The entered name is displayed on the LCD and echoed back over UART.
4. The number of characters entered is calculated and displayed via UART.
5. A 7-segment display counts up or down depending on button input.
6. Button presses change the counting direction using interrupts.
7. Timer1 controls the update rate of the 7-segment display.

---

## Interrupts Used
- **PCINT0_vect**  
  Detects button presses and updates display mode.
  
- **TIMER1_OVF_vect**  
  Updates the counter and refreshes the 7-segment display.

---

## Build Notes
- Uses direct AVR register configuration
- No Arduino `loop()` or `setup()` functions
- Designed to compile as a single `main.cpp` file
- Compatible with AVR-GCC toolchain

---

## Author
**Yoseph (Johnny) Gebre**

---

## Notes
This project was created for academic and learning purposes to demonstrate embedded programming concepts including interrupts, timers, serial communication, and peripheral control.
