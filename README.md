# Embedded C Projects – AVR Microcontroller

## Overview
This repository contains a collection of **Embedded C projects** developed for AVR microcontrollers using **direct register configuration and peripheral control**.  
The projects progressively build core embedded systems concepts including **GPIO, timers, interrupts, PWM, ADC, UART communication, LCD control, and shift registers**.

All projects are written in **C/C++ for AVR-GCC** and focus on understanding how microcontroller peripherals work together in complete systems.

---

## Key Concepts Covered
- AVR register configuration
- GPIO input/output control
- Timers and prescalers
- UART (USART) serial communication
- LCD control in 4-bit mode
- PWM for RGB LED control
- Analog-to-Digital Conversion (ADC)
- Pin Change Interrupts (PCINT)
- External Interrupts (INT0)
- Shift register communication
- Modular embedded software design

---

## Project Breakdown

### 📘 Tutorial 6 – LCD & USART
**Focus:** LCD interfacing and serial communication  
- 16x2 LCD driven in 4-bit mode  
- USART communication at 9600 baud  
- User input received via UART  
- Text displayed simultaneously on LCD and serial monitor  
- Custom delay handling without Arduino abstractions  

**Skills Demonstrated**
- LCD command and data handling  
- UART transmit and receive logic  
- Embedded string processing  

---

### 📘 Tutorial 9 – Timers, Interrupts & Shift Registers
**Focus:** Interrupt-based counters and digital output expansion  
- 7-segment display driven via a shift register (74HC595)  
- Pin Change Interrupts (PCINT) for button input  
- Timer1 overflow interrupt for periodic counting  
- Forward, reverse, and stop counter states  
- Modular driver files for interrupts and shift registers  

**Skills Demonstrated**
- Timer configuration and overflow handling  
- PCINT state change detection  
- Shift register control using GPIO  
- Interrupt-safe variable handling  

---

### 📘 Tutorial 10 – ADC & Joystick Input
**Focus:** Analog input and real-time feedback  
- ADC initialization and channel selection  
- Joystick X/Y axis reading  
- Directional LED output based on analog thresholds  
- Button press detection via GPIO  
- Debug output via USART  

**Skills Demonstrated**
- ADC setup and polling  
- Analog threshold logic  
- Integrated analog and digital inputs  

---

### 🧪 Assignment 2 – PWM, LCD, UART & External Interrupts
**Focus:** Multi-peripheral integration  
- RGB LED controlled via PWM (Timer0 & Timer2)  
- LCD displays live RGB values  
- UART accepts user input in `R G B` format  
- External interrupt (INT0) applies updates  
- Input validation and range checking (0–255)  

**Skills Demonstrated**
- PWM duty cycle control  
- External interrupt handling  
- User input parsing and validation  
- Coordinated peripheral control  

---

### 🏁 Final Integration Project
**Focus:** Complete embedded system design  
- Integrates:
  - LCD
  - UART
  - Timers
  - Pin Change Interrupts
  - Shift register
  - 7-segment display  
- User interaction through serial input  
- Interrupt-driven display updates  
- Structured modular design using headers and source files  

**Skills Demonstrated**
- Multi-module embedded application design  
- Interrupt coordination  
- Peripheral interaction  
- Real-time system behavior  

---

## Repository Structure (Conceptual)
/T6 → LCD & USART
/T9 → Timers, PCINT, shift registers
/T10 → ADC & joystick input
/A2 → PWM, INT0, RGB control
/Final → Integrated embedded system


---

## Hardware Used
- AVR microcontroller (ATmega series)
- 16x2 LCD
- Push buttons
- RGB LED
- Joystick module
- 7-segment display
- Shift register (74HC595)
- Serial interface (UART)

---

## Build & Environment
- AVR-GCC toolchain
- Standard `main()` application structure
- Compiled and tested using AVR development tools
- Debug support via `avr_debugger.h`

---

## Design Approach
- Clear separation of drivers and application logic  
- Interrupt-based event handling  
- Predictable and maintainable program flow  
- Emphasis on clarity, correctness, and modularity  

---

## Author
**Yoseph (Johnny) Gebre**  
Embedded Systems | Firmware Development | C Programming

---

## Notes
These projects were developed for academic and portfolio purposes and demonstrate practical embedded systems concepts relevant to firmware and embedded software roles.
