#include <Arduino.h>
#include <avr_debugger.h>
#include"Segment.h"
#include"ShiftReg.h"
#include "PCINT0.h"

byte digits[ARRAY_SIZE_DECIMAL] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 }; 

int main()
{
  #ifdef __DEBUG__
    dbg_start();
  #endif
 
  init_shift(DATA,CLOCK,LATCH);

  // initalize the PCINT0 (Interrupter)
  // initalize Timer1

  /* Task 1 */
  // Requires no Timers or Interrupters
  // You may use _delay_ms for ONLY task 1
  // Task 1 you must USE the function displayValue to 
  // continuesly display from 0-9.
  // Please do task1 outside your while loop.
  // You can comment it out when doing task2.
 
  while(1)
  { 
    /* Task 2 */
    // You are NOT allowed to use _delay_ms
    // You must use interrupter PCINT0
    // Note: BUTTON2 uses PCINT1 (but still uses PCINT0)
    // 
    // In here we should have 2 checks
    // 1 --> Count from 0-9
    // 2 --> Count backwords 9-0
    // 0 --> (Do nothing) We don't even need to 
    // check for this.
  }
}

/* Task2: Interrupt */
ISR(PCINT0_vect)
{
    // Before checking which button was pressed,
    // We first need to figure out which bits changed.
    // To do se we can take our current PIN value (PINB)
    // and use exclusive or on the old PIN value,
    // and store that as our changed bits to know which
    // button was pushed.
    // After we can set the current Pin value to the 
    // old Pin value for when we loop again.

    // From there we can now check using the changesbits
    // against our buttons to find which one was changed,
    // Since BUTTON1 uses PCINT0 and BUTTON2 uses PCINT1

    if (PINB & (1 << BUTTON1)) {} // WILL NOT WORK!
    // Do not do the above!!!!

    // You'll need to check which bits changed.
    byte currentPinValue = PINB;
}

/* Task2: Timer1 */
ISR(TIMER1_OVF_vect)
{
    // Don't forget to set TCNT1 (Delay time) 
    // TCTN1 = 65535 - delayTime/0.000016
    // Remember we need to put our counter in here.
    // It starts from 0 and needs to count continuously 
    // by 1 digit at a time. 
    // Note, the digit should no exceed 9.
    // You could use modulo in this case! 
}