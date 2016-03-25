#define F_CPU 2000000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define green PA7
#define red PA6
#define blue PA5
#define white PA0


void initIO(void) {
    //Set fast PWM for timer 0
    TCCR0A |= ((1 << WGM01) | (1 << WGM00));
    TCCR1A |= ((1 << WGM01) | (1 << WGM00));
    
    // clear OC0A on compare match, set on BOTTOM (inverting)
    // 255 is fully off, 0 is fully on
    TCCR0A |= ((1 << COM0A1) | (1 << COM0A0));
    TCCR1A |= ((1 << COM0A1) | (1 << COM0A0));
    
    //Use clock directly, no prescaler
    TCCR0B |= ((0 << CS02) | (0 << CS01) | (1 << CS00));
    TCCR1B |= ((0 << CS02) | (0 << CS01) | (1 << CS00));
    
    //Initialize counter for timer 0
    TCNT0 = 0;
    TCNT1 = 0;
    
    //Set LED pins as output
    DDRA |= ((1 << green) | (1 << blue) | (1 << red) | (1 << white));
}

int main(void) {
	initIO();

	while (1) {
        // fade green up
        for (int i = 0; i < 256; i++)
        {
            OCR1B = (255-i);
            _delay_ms(2);
        }
        // fade green down
        for (int j = 255; j >= 0; j--)
        {
            OCR1B = (255-j);
            _delay_ms(2);
        }
        
        
        //fade blue up
        for (int i = 0; i < 256; i++)
        {
            OCR1A = (255-i);
            _delay_ms(2);
        }
        // fade blue down
        for (int j = 255; j >= 0; j--)
        {
            OCR1A = (255-j);
            _delay_ms(2);
        }
        
        //fade red up
        for (int i = 0; i < 256; i++)
        {
            OCR0B = (255-i);
            _delay_ms(2);
        }
        // fade red down
        for (int j = 255; j >= 0; j--)
        {
            OCR0B = (255-j);
            _delay_ms(2);
        }

	}
	return 0; // never reached
}
