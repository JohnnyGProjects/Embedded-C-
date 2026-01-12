//Yoseph gebre
#include <Arduino.h>
#include <avr_debugger.h>
#include <LCD.h>
#include <USART.h>
#include "Segment.h"
#include "ShiftReg.h"
#include "PCINT0.h"

// An array of bytes representing the values to display on a 7-segment display for each decimal digit 0-9
byte digits[ARRAY_SIZE_DECIMAL] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };

// Variables for keeping track of button state and display state
volatile byte oldPortValue = 0x00;
volatile byte state = 1;
volatile byte counter = 0;

// The main function
int main()
{
  // Debugging code if __DEBUG__ is defined
  #ifdef __DEBUG__
    dbg_start();
  #endif
  
  // Initialize hardware peripherals
  USART_init();
  LCD_init();
  init_shift(DATA,CLOCK,LATCH);
  PCINT0_init();
  Timer1_init();

  // Clear the LCD screen
  LCD_command(1);

  // Create a buffer for holding user input
  char text[MAX_TEXT];
  memset(text, 0, MAX_TEXT);

  // Enter an infinite loop
  while(1)
  {
    /* Display Prompt/Get input */
    // Prompt the user to enter their name over UART and on the LCD screen
    USART_send_string("Enter your name: ");
    LCD_string("Enter your name: ");
    // Wait for user input
    USART_get_string(text);

    /* Display Name to user */
    // Display the entered name on the second line of the LCD screen and over UART
    LCD_command(0xC0);
    USART_send_string("\nName is ");
    USART_send_string(text);
    LCD_string("Name is ");
    LCD_string(text);

    /* Display in UART characters */
    // Display the length of the entered name in characters over UART
    sprintf(text, "%d", strlen(text));
    USART_send('\n');
    USART_send_string("Your name has ");
    USART_send_string(text);
    USART_send_string(" character(s)\n\n");
  
    /* Wait 3 seconds then clear name and screen */
    // Wait 3 seconds before clearing the entered name and the LCD screen
    delayMs(3000);
    LCD_command(0x80);
    LCD_command(1);
    memset(text, 0, MAX_TEXT);

    // Update the 7-segment display
    if(state == 1)
    {
      displyValue(digits[counter]);
    }else if(state == 2)
    {
      displyValue(digits[9 - counter]);
    }
  }
}

// Interrupt service routine for the PCINT0 interrupt
ISR(PCINT0_vect)
{
  byte changedbits;
  byte currentPortValue = PINB;
  
  changedbits = currentPortValue ^ oldPortValue;
  oldPortValue = currentPortValue;

  // Check if button 1 has been pressed and update the display state accordingly
  if (changedbits & (1 << BUTTON1))
  {
    state = 0;
  }

  // Check if button 2 has been pressed and update the display state accordingly
  if (changedbits & (1 << BUTTON2))
  {
    state = 2;
  }
}

// Interrupt service routine for the TIMER1 overflow interrupt
ISR(TIMER1_OVF_vect)
{
  // If the display state is 0, reset the timer to its maximum value
  if(state == 0)
  {
    TCNT1 = 65535;
  } else
  {
    TCNT1 = 34285;
    counter = (counter+1)%10;
  }
}