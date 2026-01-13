# 📟 LCD Name Entry System using USART (AVR / Arduino)

An embedded systems project that demonstrates **USART serial communication**, **LCD interfacing in 4-bit mode**, and **string handling** on an Arduino-compatible AVR microcontroller.

The application prompts a user to enter their name via a serial terminal, displays the input on a 16×2 LCD, calculates the character count, and outputs feedback over USART.

## 🧩 Module Overview

### 🧠 `main.cpp`

* Entry point of the application
* Initializes USART and LCD
* Prompts user to enter their name via serial terminal
* Displays prompt and user input on LCD
* Prints the entered name and character count via USART
* Clears LCD after a delay and repeats the process

---

### 📟 `LCD.h / LCD.cpp`

* Implements a **16×2 character LCD driver** in **4-bit mode**
* Uses direct register manipulation
* Supports:
  * LCD initialization sequence
  * Command writing
  * Character and string display
  * Cursor positioning
* Uses timing-safe delays for LCD instruction execution

---

### 📡 `USART.h / USART.cpp`

* Configures USART for:
  * 9600 baud rate
  * 8 data bits
  * 1 stop bit
* Sends individual characters and strings
* Receives user input from serial terminal
* Echoes characters and handles string termination

---

## ⚙️ Core Functionality

* Prompts user for input via USART
* Reads string input character-by-character
* Displays prompt and user name on LCD
* Calculates and displays character count
* Outputs formatted debug and feedback messages
* Clears display after a timed delay
* Runs continuously in a loop

---

## 🧠 Embedded Systems Concepts Demonstrated

* USART serial communication
* LCD interfacing (4-bit mode)
* Register-level I/O control
* Timing-critical peripheral initialization
* String handling in embedded C/C++
* Blocking input/output behavior
* Hardware abstraction through modular drivers

---

## 🛠️ Technologies Used

* C / C++
* Arduino framework
* AVR microcontroller registers
* 16×2 character LCD
* USART serial communication
* Embedded delay handling

---

## ▶️ How It Works (High Level)

1. System initializes USART and LCD controller
2. User is prompted to enter their name via serial terminal
3. Input is received character-by-character
4. Name is displayed on the LCD
5. Character count is calculated and printed over USART
6. LCD clears after a delay and restarts the process

---

## 🎯 Project Purpose

This project was created to:

* Practice USART communication and debugging
* Interface an LCD using 4-bit data mode
* Handle user input in embedded systems
* Demonstrate modular driver-based design
* Reinforce timing and hardware initialization concepts

---

## 👨‍💻 Author

**Johnny (Yoseph Gebre)**  
IT Graduate — Carleton University  
Interest in embedded systems, firmware development, and hardware-software integration

---

## 📄 License

This project is for educational and portfolio purposes.


