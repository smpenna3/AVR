#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    
    //Set all of Port D to output
    DDRD = 0xFF;
    
    
    while(1){
        PORTD |= _BV(PD5);
        
        _delay_ms(1000);
        
        PORTD &= ~_BV(PD5);
        
        _delay_ms(1000);
    }
    
    
	return 0; // never reached
}
