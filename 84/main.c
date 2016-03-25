#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    
    //Set all of Port D to output
    DDRA = 0xFF;
    
    
    while(1){
        PORTA |= _BV(PA0);
        
        _delay_ms(1000);
        
        PORTA &= ~_BV(PA0);
        
        _delay_ms(1000);
    }
    
    
	return 0; // never reached
}
