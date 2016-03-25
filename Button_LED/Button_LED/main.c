#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    //Make all port D output
    DDRD |= (1 << PD5);
    
    //Make all port C input
    DDRC &= ~(1 << PC5);
    
    PORTC |= (1 << PC5);
    
    while(1){
        //If switch is pressed
        while((PINC & _BV(PD5)) == 0){
            PORTD = 0xFF;
        }
        
        PORTD = 0x00;
    }
}