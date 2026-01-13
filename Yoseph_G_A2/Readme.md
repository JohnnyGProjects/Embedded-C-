# 🎨 RGB LED Controller with LCD, USART, PWM, and External Interrupts

This project implements an **RGB LED control system** using an **Arduino-compatible AVR microcontroller**, integrating **USART serial communication**, **PWM-based LED control**, a **16x2 LCD display**, and **external interrupts (INT0)**.  
The system allows users to input RGB values via serial communication, display the values on an LCD, and update LED brightness using hardware PWM.

## 🧩 Module Overview

### 🧠 `main.cpp`

* Entry point of the application
* Initializes USART, LCD, PWM, and INT0
* Handles user input validation and parsing
* Maintains current RGB values
* Updates LCD and RGB LED output
* Contains the `INT0_vect` interrupt service routine

---

### 🔘 `INT0.h / INT0.cpp`

* Configures **external interrupt INT0 (PD2)**
* Uses falling-edge trigger with internal pull-up
* Handles button press events
* Used to confirm and apply RGB value updates

---

### 🖥️ `LCD.h / LCD.cpp`

* Controls a **16x2 character LCD** in 4-bit mode
* Implements:
  * LCD initialization sequence
  * Command and data writes
  * String output
* Uses direct port manipulation for precise timing

---

### 🎛️ `PWM.h / PWM.cpp`

* Configures hardware PWM using **Timer0 and Timer2**
* Controls RGB LED brightness:
  * Red → OCR0A
  * Blue → OCR0B
  * Green → OCR2B
* Updates LED intensity using duty cycle values (0–255)

---

### 📡 `USART.h / USART.cpp`

* Configures USART for **9600 baud, 8-bit data**
* Sends and receives characters and strings
* Accepts user input in the format:

R G B

Example:


100 50 255

* Echoes user input for confirmation

---

## ⚙️ Core Functionality

* Accepts RGB values via serial terminal
* Validates numeric input and range (0–255)
* Displays current RGB values on an LCD
* Updates RGB LED brightness using PWM
* Uses **INT0 button press** to apply and confirm changes
* Prevents unintended multiple triggers using state tracking

---

## 🧠 Embedded Systems Concepts Demonstrated

* External interrupts (INT0)
* Hardware PWM (Timer0 & Timer2)
* USART serial communication
* LCD interfacing in 4-bit mode
* Direct register manipulation
* Interrupt Service Routines (ISR)
* Input validation and parsing
* Volatile and state-based interrupt handling

---

## 🛠️ Technologies Used

* C / C++
* Arduino framework (minimal abstraction)
* AVR libraries
* ATmega microcontroller architecture
* 16x2 character LCD
* RGB LED
* Hardware timers and interrupts

---

## ▶️ How It Works (High Level)

1. User enters RGB values via serial terminal
2. Input is validated and parsed
3. Values are stored but not immediately applied
4. Pressing the INT0 button confirms the update
5. LCD updates to display current RGB values
6. PWM duty cycles update LED brightness

---

## 🎯 Project Purpose

This project was created to:

* Demonstrate integration of multiple hardware peripherals
* Practice interrupt-driven embedded system design
* Implement USART-based user interaction
* Control LEDs using hardware PWM
* Interface with an LCD using low-level register control

---

## 👨‍💻 Author

**Johnny (Yoseph Gebre)**  
IT Graduate — Carleton University  
Interest in embedded systems, firmware development, and hardware-software integration

---

## 📄 License

This project is for educational and portfolio purposes.

