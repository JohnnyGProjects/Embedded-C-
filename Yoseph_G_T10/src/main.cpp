#include <Arduino.h>
#include <avr_debugger.h>

#include <USART.h>
#include"ADC.h"

/* Define Data */
#define LED_CENTER PB0
#define LED_TOP PB1
#define LED_RIGHT PB2
#define LED_BOTTOM PB3
#define LED_LEFT PB4
#define JBUTTON PD2

#define CENTER 512
#define HALFWAY 256
int xValue=512;
int yValue=220;
int bValue=0;

/* Task 1 */
int main()
{
	char text[MAX_TEXT];
	DDRB = 0x1F;
	DDRD &= ~(1<<JBUTTON);
	PORTD|=(1<<JBUTTON);

	USART_init();	// initialize USART
	ADC_Init(); 	// initialize ADC
	
	while(1)
	{
		xValue = ADC_Read(PC0); // Read in the X-axis
	  		
			if(xValue > CENTER + HALFWAY)	// x > 768
			{
				PORTB = 0x04; //right led on
			} else if (xValue < CENTER - HALFWAY) // x < 256
			{
				PORTB = 0x10; //left led on
			}

		yValue = ADC_Read(PC1); // Read in the Y-axis (Remeber to clear PC1 in ADC.cpp)

			if(yValue > CENTER + HALFWAY)	// y > 768
			{
				PORTB = 0x08; //top led on
			} else if (yValue < CENTER - HALFWAY) // y < 256
			{
				PORTB = 0x02; //bottom led on
			}
			// if(xValue > 256 && xValue < 768 && yValue > 256 && yValue < 768)
			if(xValue > CENTER - HALFWAY && xValue < CENTER + HALFWAY && 
			yValue > CENTER - HALFWAY  && yValue < CENTER + HALFWAY)
			{
				PORTB = 0x01; //center led on
			}

			/*  this portion is when the joystick button
				is pressed we want all LEDs to turn on
			*/
			bValue = PIND & (1<<JBUTTON);
			if(!bValue)	//if ((PIND & (1 << SW_pin)) == LOW) // Same method
			{
				PORTB = 0x1F; //all leds on
				USART_send_string("Button was pressed!\n");
			}
	
		// Print data for debugging
		sprintf(text, "x = %d & y= %d & b= %d \n", xValue, yValue, bValue);
		USART_send_string(text);
		_delay_ms(100);
  	}
}

/* Task 2 */
int main()
{
	char text[MAX_TEXT];
	DDRB = 0x0F;

	USART_init();	// initialize USART
	ADC_Init(); 	// initialize ADC

	while(1)
	{
		//used value just to test they need to divide 1024 by 5
		xValue = ADC_Read(PC0); 
		//xValue /=	57;	
		sprintf(text, "x = %d  \n", xValue);
		USART_send_string(text);
		_delay_ms(100);

		/* Just note xValue (minimum value and maximum value)  */
		if(xValue < 100)
		{
			PORTB= 0x00; 	// no LED on
		}else if(xValue <200)
		{
			PORTB= 0x01;	// first LED on
		}else if(xValue<300)
		{
			PORTB= 0x03; 	// First and second on
		}else if(xValue<350)
		{
			PORTB= 0x07; 	// frist second and third on
		}else{
			PORTB= 0x0F; 	// all LEDs on
		}
  	}
}
