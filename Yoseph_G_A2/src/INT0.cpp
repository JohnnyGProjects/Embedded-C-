#include <INT0.h>

void INT0_init(void)
{
    // PD2 is now an input with pull-up enabled
    DDRD &= ~(1 << BUTTON);    // Set Pin 2 as input
    PORTD |= (1 << BUTTON);

    EICRA |= (1 << ISC01);    // set INT0 to trigger on Falling edge logic change
    EIMSK |= (1 << INT0);     // Turns on INT0
    sei();                    // turn on interrupts
}