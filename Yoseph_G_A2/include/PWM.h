#pragma once
#include <Arduino.h>

// Defines Variables
#define LEDBLUE PD5
#define LEDRED PD6
#define LEDGREEN PD3

//Function Prototypes
void PWM_init(void);
void setDutyCycle(byte d0A, byte d0B, byte d2B);
