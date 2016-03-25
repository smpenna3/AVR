#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    
    //Set all of Port D to output
    DDRD = 0xFF;
    
    int time_delay = 500;
    
    while(1){
        //Set PD6 to high, all else to low
        PORTD |= (1 << PD6);
        PORTD &= ~(1 << PD5);
        PORTD &= ~(1 << PD3);
     
        //delay time_delay seconds
        _delay_ms(time_delay);
     
        
        //Set PD7 to high, all else low
        PORTD |= (1 << PD3);
        PORTD &= ~(1 << PD5);
        PORTD &= ~(1 << PD6);
     
        //delay time_delay seconds
        _delay_ms(time_delay);
     
        
        //Set PD5 to high, all else low
        PORTD |= (1 << PD5);
        PORTD &= ~(1 << PD6);
        PORTD &= ~(1 << PD3);
     
        //delay time_delay seconds
        _delay_ms(time_delay);

    }
    
    
	return 0; // never reached
}
