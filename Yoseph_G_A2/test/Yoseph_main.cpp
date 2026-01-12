#include <Arduino.h>
#include <avr_debugger.h>
#include <LCD.h>
#include <USART.h>
#include"PWM.h"
#include"INT0.h"

volatile byte red=0, green=0, blue=0, redChange=0, greenChange=0, blueChange=0;

int main()
{
    #ifdef __DEBUG__
      dbg_start();
    #endif

	char text[MAX_TEXT];
	char *token;

	//initialize interrupt
	INT0_init();
	//initialize PWM on Timer0 and Timer2
	PWM_init();

	// initialize USART/LCD controller
    USART_init();
	LCD_init();

	// clear LCD display
	LCD_command(1);

	//reading the initial values of RGB
	memset(text, 0, MAX_TEXT);
	// Display Prompt/Get initial values for RGB
	USART_send_string((char*)"Type valid values for R G B color (use space between values) ");
	USART_get_string(text);

	LCD_command(0x80);  // Move to first line
	LCD_command(1);	 	// Clear screen
	//tokenize the value entered for RGB and convert to int between 0 to 255
	token = strtok(text, " ");
	red = atoi(token)%256;

	token = strtok(NULL, " ");
	green = atoi(token)%256;

	token = strtok(NULL, " ");
	blue = atoi(token)%256;

	//Generate PWM to create RGB on LED
	setDutyCycle(red, green, blue);
	//Display the Current value of RGB on LCD
	LCD_string((char*)"Current Values:");
	LCD_command(0xC0); // Move to second line
	sprintf(text, "R%d G%d B%d", red, green, blue);
	LCD_string(text);
	//go to new line in console
	USART_send('\n');

    while(1)
    {
		//reading change values for RGB
		USART_send_string((char*)"Type valid values to be added to R G B color (use space between values) ");
		USART_get_string(text);
		USART_send('\n\n');
		//tokenize the values entered for change RGB and convert to int between 0 to 255
		token = strtok(text, " ");
		redChange = atoi(token)%256;

		token = strtok(NULL, " ");
		greenChange = atoi(token)%256;

		token = strtok(NULL, " ");
		blueChange = atoi(token)%256;

		//reset text to 0
		memset(text, 0, MAX_TEXT);

		//wait for interrupt or get new change values
    }
}

//Intrrupt Service Routine
ISR(INT0_vect)
{
  char text[MAX_TEXT];
  //update the RGB by adding the change value ensure value between 0 and 255
  red = (red+redChange) % 256;
  green = (green+greenChange) % 256;
  blue = (blue+blueChange) % 256;
  //Generate PWM to create RGB on LED based on updated values
  setDutyCycle(red, green, blue);

  // Display The new value of RGB on LCD
  LCD_command(0xC0); // Move to second line
  sprintf(text, "R%d G%d B%d ", red, green, blue);
  LCD_string(text);

}