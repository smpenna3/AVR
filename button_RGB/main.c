#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {
    
    //Set LED pins to output
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD6);
    DDRD |= (1 << PD7);
    
    //Set button pin to input
    DDRB |= (0 << PB1);
    
    int time_delay = 500;
    
    int i = 0;
    
    while(1){
        
        //If the button is pressed
        if(PINB & (1 << PB1) == 1){
            i++;
            if(i = 3){i = 0;}
        }
        
        if(i == 0){
            PORTD |= (1 << PD6);
            PORTD &= ~(1 << PD5);
            PORTD &= ~(1 << PD7);
        }
        
        else if(i == 1){
            PORTD |= (1 << PD7);
            PORTD &= ~(1 << PD5);
            PORTD &= ~(1 << PD6);
        }
        
        else if(i == 2){
            PORTD |= (1 << PD5);
            PORTD &= ~(1 << PD6);
            PORTD &= ~(1 << PD7);
        }
        
    }
    
    
	return 0; // never reached
}
