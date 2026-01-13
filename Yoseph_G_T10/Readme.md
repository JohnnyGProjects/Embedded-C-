# 🕹️ Joystick Direction Indicator using ADC and USART (AVR / Arduino)

This project implements a **joystick-controlled LED direction indicator** using an **Arduino-compatible AVR microcontroller**.  
It uses the **Analog-to-Digital Converter (ADC)** to read joystick X/Y positions, controls multiple LEDs to indicate direction, and outputs debug data over **USART serial communication**.

The system demonstrates ADC configuration, real-time input processing, and direct hardware control using AVR registers.

## 🧩 Module Overview

### 🧠 `main.cpp`

* Entry point of the application
* Reads joystick X and Y axis values using ADC
* Determines joystick direction based on threshold ranges
* Controls LEDs to indicate direction:
  * Center
  * Up
  * Down
  * Left
  * Right
* Detects joystick button press
* Outputs ADC values and button state over USART for debugging

---

### 🔌 `ADC.h / ADC.cpp`

* Configures the AVR **Analog-to-Digital Converter**
* Uses:
  * AVcc as voltage reference
  * Prescaler set to 128
  * Polling-based conversion
* Supports reading from selectable ADC channels
* Returns 10-bit ADC values (0–1023)

---

### 📡 `USART.h / USART.cpp`

* Configures USART for **9600 baud**, 8-bit data
* Sends characters and formatted strings
* Used for debugging and monitoring joystick values
* Outputs real-time ADC readings to a serial terminal

---

## ⚙️ Core Functionality

* Reads joystick X-axis and Y-axis positions via ADC
* Uses threshold-based logic to determine direction
* Lights corresponding LEDs based on joystick movement
* Turns on all LEDs when joystick button is pressed
* Sends joystick position and button state to serial output
* Supports multiple task configurations for different behaviors

---

## 🧠 Embedded Systems Concepts Demonstrated

* Analog-to-Digital Conversion (ADC)
* Joystick input processing
* Threshold-based decision logic
* Direct register manipulation (`DDRx`, `PORTx`, `PINx`)
* USART serial communication
* Real-time hardware interaction
* Debugging via serial output

---

## 🛠️ Technologies Used

* C / C++
* Arduino framework (minimal abstraction)
* AVR libraries
* ATmega microcontroller architecture
* Analog joystick module
* LEDs
* USART serial communication

---

## ▶️ How It Works (High Level)

1. Joystick X and Y axes are read using ADC channels
2. ADC values are compared against predefined thresholds
3. Corresponding LEDs indicate joystick direction
4. Pressing the joystick button turns on all LEDs
5. ADC values and button state are sent over USART

---

## 🎯 Project Purpose

This project was created to:

* Demonstrate ADC configuration and usage
* Practice processing analog input signals
* Interface a joystick with an AVR microcontroller
* Control multiple outputs using sensor input
* Debug embedded systems using serial communication

---

## 👨‍💻 Author

**Johnny (Yoseph Gebre)**  
IT Graduate — Carleton University  
Interest in embedded systems, firmware development, and hardware-software integration

---

## 📄 License

This project is for educational and portfolio purposes.

