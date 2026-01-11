#include <Arduino.h>
#include <avr_debugger.h>
#include <LCD.h>
#include <USART.h>

int main()
{
    #ifdef __DEBUG__
      dbg_start();
    #endif

    char text[MAX_TEXT];
    
	// initialize USART/LCD controller
    USART_init();
	LCD_init();

	// clear LCD display
	LCD_command(1);

    while(1)
    {
		memset(text, 0, MAX_TEXT);
		/* Display Prompt/Get input */
		USART_send_string("Enter your name: ");
		LCD_string("Enter your name: ");
		USART_get_string(text);

		/* Display Name to user */
		LCD_command(0xC0); // Move to second line
		USART_send_string("\nName is ");
		USART_send_string(text);
		LCD_string("Name is ");
		LCD_string(text);

		/* Display in UART characters */
		sprintf(text, "%d", strlen(text));
		USART_send('\n');
		USART_send_string("Your name has ");
		USART_send_string(text);
		USART_send_string(" character(s)\n\n");
		
		/* Wait 3 seconds then clear name and screen */
		delayMs(3000);		// Wait 3 seconds
		LCD_command(0x80);  // Move to first line
		LCD_command(1);	 	// Clear screen
		memset(text, 0, MAX_TEXT);
    }
}