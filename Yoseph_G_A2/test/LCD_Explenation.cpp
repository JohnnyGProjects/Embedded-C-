#include <LCD.h>

// initialize port pins then initialize LCD controller
void LCD_init(void)
{
	PORTS_init();

	delayMs(100); // LCD controller reset sequence
	LCD_nibble_write(0x30, 0);
	delayMs(5);
	LCD_nibble_write(0x30, 0);
	delayMs(1);
	LCD_nibble_write(0x30, 0);
	delayMs(1);

	LCD_nibble_write(0x20, 0); // use 4-bit data mode
	delayMs(1);
	LCD_command(0x28); // set 4-bit data, 2-line, 5x7 font
	LCD_command(0x06); // move cursor right
	LCD_command(0x01); // clear screen, move cursor to home
	LCD_command(0x0F); // turn on display, cursor blinking
}

// Initialize ports to output mode
void PORTS_init(void)
{
	// PB4 for LCD R/S
	// PB2 for LCD EN
	DDRB |= (1 << RS) | (1 << EN); // set pin output mode
	PORTB &= ~(1 << EN);		   // turn off EN

	// PD4-PD7 for LCD D4-D7, respectively. (Both are the same)
    DDRD |= (1 << D4 | 1 << D5 | 1 << D6 | 1 << D7);
    /* How to find it in hexa decimal:
        D4=DDD4(4) D5=DDD5(5) D6=DDD6(6) D7=DDD7(7) 
        1<<4=16 1<<5=32 1<<6=64 1<<7=128
        16|32 = 48|64 = 112|128 = 240 -> in hexa: 0xF0
    */
	DDRD |= 0xF0; // set pin output mode

    /* compensate for the PORTC pins */
    // C0-C3 DDRC
}

/* Each 4 bits is called a nibble. This function will shift the first 4 or second 4 bits */
void LCD_nibble_write(uint8_t data, uint8_t control)
{
    /* When we send data to the LCD we need to
       send it 4 bits at a time.

       D0=DDD0(0) D1=DDD1(1) D2=DDD2(2) D3=DDD3(3) 
       1<<0=1 1<<1=2 1<<2=4 1<<3=8
       1|2 = 3|4 = 7|8 = 15 -> in hexa: 0x0F
       
       PORTD -> 8 Bits: 0---4---7
       0xF0(240) -> Covers the bits 4-7 --> 1111 0000 (Upper)
       0x0F(15)  -> Covers the bits 0-3 --> 0000 1111 (Lower)

        
       Since we are writing to PORTD we only care for the top 4 bits
       hence why we & 0xF0
    */
       
	// populate data bits
	PORTC = (data & 0x0F) >> 4; // set data bits

    /* we need to set the data bits depending on PORTC */
    // With math it actually is the same as the PORTDs lower bits (0xF0 15).


	// set R/S (Register Select) bit
	if (control & RS)   
	{
		PORTB |= (1 << RS); // Data then set RS 1
	}
	else
	{
		PORTB &= ~(1 << RS); // Command set RS 0
	}

	// pulse E (pulse the LCD)
	PORTB |= (1 << EN);	 // pulse E high
	PORTB &= ~(1 << EN); // clear E
}

void LCD_command(uint8_t command)
{
	LCD_nibble_write(command & 0xF0, 0); // upper nibble first the top 4 bits
	LCD_nibble_write(command << 4, 0);	 // then lower nibble the bottom 4 bits

    /* This is if you want to adjust the upper/lower nibble before you enter LCD_nibble:
	// As the upper and lower nibble have essentially swaped, we need to compensate */
    // upper nibble is actually almost setup for PORTC
    //
    //    PORTC -> 8 Bits: 7---4---0 (technically only 6 usable bits 5-0)
    //    0x0F(15)  -> Covers the bits 3-0 --> 0000 1111 (Upper)
    //    0xF0(240) -> Covers the bits 7-4 --> 1111 0000 (Lower)
    //
    // If ANDing 0xF0 covered the first four bits in PORTD and is now the last 4 bits on PORTC then 
    // then all we have to do is SHIFT it to the right by 4 bits
    //
    // Now for the lower nibble we just do what we did for the upper nibble on PORTD
    // Since we are using PORTC it will write for the lower nibble.
    // command & (upper nibble)

	/* Note the other method to setting the correct upper/lower nibble is to use the same logic for the upper nibble here
	   but use it where we populate the data bits. That way we don't need to modify how we call LCD_nibble_write */

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
    // This should follow the exact same in LCD_command but instead will send
    // our register select.
	LCD_nibble_write(data & 0xF0, RS); // upper nibble first
	LCD_nibble_write(data << 4, RS);   // then lower nibble

	delayMs(1);
}

//send string to LCD
void LCD_string(char *str)
{
  byte i;
  for(i=0; str[i] !='\0';i++)
  {
    LCD_data(str[i]);
  }
}

//_delay_ms( ), expects a constant, therefore,
// you can use this delay function which accepts a
// variable delay time
void delayMs(uint16_t ms)
{
	while (ms > 0)
	{
		_delay_ms(1);
		ms--;
	}
}