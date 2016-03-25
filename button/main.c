#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    //Make all port D output
    DDRD = 0xFF;
    
    //Make all port C input
    DDRC = 0x00;
    
        while(1){
            //If switch is pressed
            if(PINC & (1<<PC5) == 1){
                PORTD = 0xFF; //Turns ON LED
                _delay_ms(3000); //3 second delay
                PORTD = 0x00; //Turns OFF LED
            }
    }
}