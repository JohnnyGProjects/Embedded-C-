/* Assignment 2 */
#include <Arduino.h>
#include <avr_debugger.h>
#include <LCD.h>
#include <USART.h>
#include <PWM.h>
#include <INT0.h>

// Defines Variables
char rgbString[MAX_TEXT];   // This holds the input from the user
int rgbValue[3] = {0,0,0};  // Array that will hold our 3 digits.
int newValue[3] = {0,0,0};  // Array that will have values be added to.
const char delim[2] = " ";  // Delimiter, holds the space character
boolean lastInterrupt = false; // This should solve double interrupts issue
boolean firstprompt = false; // Begin with first prompt.

// Function Prototypes
void outputLCD();

int main()
{
    #ifdef __DEBUG__
      dbg_start();
    #endif

	// initialize USART/LCD/Timer0_2PWM/INT0 controller
  USART_init();
  LCD_init();
  PWM_init();
  INT0_init();

	// clear LCD display
	LCD_command(1);
  boolean valid = false;  // Begin with the our RGB values as invlaid

  outputLCD(); // Output the default RGB values

  while(1)
  {
    while (valid != true)
    {
      memset(rgbString, 0, MAX_TEXT); // Reset Our Input String

      /* Get user input  */
      if(!firstprompt)  // Just note, the first prompt will appear even if you push the button once. Due to order of operation.
      {
        USART_send_string("\nType valid values for R G B color (use space between values): ");
      } else 
      {
        USART_send_string("\nType valid values to be added to R G B colour (space between values): ");
      }
      
      USART_get_string(rgbString);
      USART_send('\n'); // Formatting

      /* Lets confirm our string only contains spaces, null term, newline, and digits! */
      for(int i = 0; i <= strlen(rgbString); i++)
      {
        // Note negatives arn't required (I just have it).
        if( !(isdigit(rgbString[i])) && rgbString[i] != ' ' && rgbString[i] != '\0' && rgbString[i] != '\r' && rgbString[i] != '\n' && rgbString[i] != '-')
           {
              valid = false;
              USART_send_string("WARNING! INVALID INPUT DETECTED");
              break;
           }
           else 
           {
              valid = true; // For now our numbers are valid!
           }
      }

      if(valid == false) continue;  // Start over, get input again if invalid!

      /* Now lets extract the digits (Example: "10 20 30") */
      char* token;  // Will hold our number
      token = strtok(rgbString, delim);
      byte index = 0;       // This will tell us how many numbers we saved.
      while (token != NULL) // Loop untill there is nothing left to save
      {
        int tempNum = atoi(token);  // Convert our number to a integer using atoi!
        if(tempNum % 256 == tempNum)  // Check if our number is in range from 0-255 using modulo(%)
        {
          valid = true; // This should already be true, but as a sanity check.
          newValue[index] = tempNum;  // Store our digit in an array for later.
          index++;                    // Next number
          token = strtok(NULL, delim); // Get next token
        } else // Our number is not within the range
        {
          valid = false;  // Send back to get input again.
          USART_send_string("WARNING! NUMBER(S) IS OUT OF RANGE!\n");
          break; // Leave the loop
        }
      }

      /* We must make sure we only have 3 numbers.
         If we have more or less then we should ask for input again */
      if(index != 3 && valid == true) // disregard printing if there already is an error
      {
        valid = false;
        USART_send_string("WARNING! INVALID AMOUNT OF VALUES!\n");
      }

    }

    /* We need to reset some values before restarting */
    memset(rgbString, 0, MAX_TEXT); // Reset out input array
    valid = false;  // Set back our RGB values as invalid to rerun the loop
  }
}

/* Output the current RGB values to the LCD*/
void outputLCD()
{
  LCD_command(1); // Reset screen and return to home
  LCD_string("Current Values: ");
  LCD_command(0xC0); // Move cursor to 2nd line
  for(int i = 0; i <= 2; i++)
  {
    rgbValue[i] = ( rgbValue[i] + newValue[i] ) % 256; // Saftey net to catch any value over 256
    if (rgbValue[i] < 0) rgbValue[i] = 0;  // Not necessary. This is to deal with negatives, to make sure we don't go below 0
  }
  sprintf(rgbString, "R%d G%d B%d", rgbValue[0], rgbValue[1], rgbValue[2]); // Now display
  LCD_string(rgbString);
  memset(rgbString, 0, MAX_TEXT); // Reset out input array
}

ISR (INT0_vect) // INT0 interrupts for PD2
{
    if(!firstprompt) firstprompt = true;  // Next prompt is to add the value

    /* Due to the button being pressed twice,
       We can adjust our code to always skip the
       second input. */
    if(!lastInterrupt)
    {
      outputLCD();  // Update with the new rgbValues.
      // Now output to LED
      setDutyCycle(rgbValue[0], rgbValue[1], rgbValue[2]);
      lastInterrupt = true;
    } else 
    {
      lastInterrupt = false;
    }
    delayMs(500); // Wait before looping again to avoid multiple inputs
}

/* 
   Therefore below counts as being 100% valid

ISR (INT0_vect) // INT0 interrupts for PD2
{
      outputLCD();  // Update with the new rgbValues.
      // Now output to LED
      setDutyCycle(rgbValue[0], rgbValue[1], rgbValue[2]);
}
*/
