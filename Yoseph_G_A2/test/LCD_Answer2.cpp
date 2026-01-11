#include <LCD.h>

// Initialize ports to output mode
void PORTS_init(void)
{
	// PB1 for LCD R/S
	// PB0 for LCD EN
	DDRB |= (1 << RS) | (1 << EN); // set pin output mode
	PORTB &= ~(1 << EN);		   // turn off EN

	// PC0-PC3 for LCD D4-D7, respectively.
	/* Both lines below are the same. The math equals to 15 */
	//DDRC |= 0x0F; // set pin output mode
	DDRC |= (1 << D4 | 1 << D5 | 1 << D6 | 1 << D7); // set pin output mode
}

void LCD_nibble_write(uint8_t data, uint8_t control)
{

	// populate data bits
	/*  shift right 4 bits
			  They could also do this in LCD_data/LCD_command when
			  they call LCD_nibble_write	*/
	PORTC = data & 0x0F; // set data bits

	// set R/S bit
	if (control & RS)
	{
		PORTB |= (1 << RS);
	}
	else
	{
		PORTB &= ~(1 << RS);
	}

	// pulse E
	PORTB |= (1 << EN);	 // pulse E high
	PORTB &= ~(1 << EN); // clear E
}

void LCD_command(uint8_t command)
{
	LCD_nibble_write((command & 0xF0) >> 4, 0); // upper nibble first
	LCD_nibble_write(command & 0x0F, 0);	 // then lower nibble

	if (command < 4)
	{
		delayMs(2); // command 1 and 2 needs up to 1.64ms
	}
	else
	{
		delayMs(1); // all others 40 us
	}
}

void LCD_data(uint8_t data)
{
	LCD_nibble_write((data & 0xF0)>>4, RS); // upper nibble first
	LCD_nibble_write(data & 0x0F, RS);   // then lower nibble

	delayMs(1);
}

