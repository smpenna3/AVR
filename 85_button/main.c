#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    
    //Set pin PB4 to output
    DDRB |= _BV(PB4);
    
    //Set pin PB2 to input
    DDRB &= ~_BV(PB2);
    
    
    while(1){
        
        if(PINB & (1<<PB2)){
            PORTB |= _BV(PB4);
            
            _delay_ms(1000);
            
            PORTB &= ~_BV(PB4);
        }
    }
    
    
	return 0; // never reached
}
