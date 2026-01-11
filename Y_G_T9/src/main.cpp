/* Tutorial 9  */
#include <Arduino.h>
#include <avr_debugger.h>
#include"Segment.h"
#include"ShiftReg.h"
#include"PCINT0.h"

byte digits[ARRAY_SIZE_DECIMAL] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 }; 

volatile byte oldPortValue = 0x00; // pull up means high as defualt
volatile byte state = 1; //state 0 is off state 1 is on state 2 is on reverse
volatile byte counter = 0;

int main()
{
  #ifdef __DEBUG__
    dbg_start();
  #endif
 
  init_shift(DATA,CLOCK,LATCH);

  PCINT0_init();
  Timer1_init();
  
  // Task1 - Not timers/interupts
  /*for(int i=0; i<ARRAY_SIZE_DECIMAL; i++)
  {
      displyValue(digits[i]);
      _delay_ms(500);
  }*/

  while(1)
  {
    if(state == 1)
    {
      //for(int i=0; i<ARRAY_SIZE_DECIMAL; i++)  // For testing without timers
      //{
          displyValue(digits[counter]);
         // _delay_ms(500);
      //}
    }else if(state == 2)
    {
      //for(int i=ARRAY_SIZE_DECIMAL-1; i>=0; i--) // For testing without timers
      //{
          displyValue(digits[9 - counter]);
         // _delay_ms(500);
     // }
    }
  }
}

ISR(PCINT0_vect)
{
  byte changedbits;
  // check which bits have changed since last interrupt
  byte currentPortValue = PINB;
  
  changedbits = currentPortValue ^ oldPortValue; //X0R
  oldPortValue = currentPortValue;

  if (changedbits & (1 << BUTTON1)) // PCINT0 changed 
  {
    state = 0;  // Stop counting
  }

  if (changedbits & (1 << BUTTON2)) // PCINT1 changed 
  {
    state = 2;  // Count reverse
  }
}

ISR(TIMER1_OVF_vect)
{
    if(state == 0)  // If the counter has stopped
    {
      TCNT1 = 65535;  // Pause the timer 
    } else
    {
      TCNT1 = 34285; // Otherwise our counter should be running
    /*
      // Without using Modulo
      if (counter >= 9)
      {
        counter = 0;
      } else {
        counter = counter + 1;
      }
    */
      // Using Modulo
      counter = (counter+1)%10;
    }
}
  


