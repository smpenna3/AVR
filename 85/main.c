#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    
    //Set all of Port D to output
    DDRB = 0xFF;
    
    
    while(1){
        PORTB |= _BV(PB4);
        
        _delay_ms(1000);
        
        PORTB &= ~_BV(PB4);
        
        _delay_ms(1000);
    }
    
    
	return 0; // never reached
}
