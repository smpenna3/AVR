#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define button PC5
#define button_interrupt PCINT13

void green(int intensity){
    OCR0A = (255-intensity);
}

void blue(int intensity){
    OCR0B = (255-intensity);
}

void red(int intensity){
    OCR2B = (255-intensity);
}

void initIO(void) {
    //Define PC3 as input with pullup-resistor
    DDRC &= ~(1 << button);
    PORTC |= (1 << button);
    
    //Enable interrupt for PCINT_11
    PCICR |= _BV(PCIE1);
    PCMSK1 |= (_BV(button_interrupt));
    
    // Fast PWM mode for timers 0 and 2
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    
    // clear OC0A on compare match, set on BOTTOM (inverting)
    // 255 is fully off, 0 is fully on
    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0);
    TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
    
    // Use clock directly, no prescaler
    TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
    TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
    
    // initialize counter for TIMER 0 and TIMER 2
    TCNT0 = 0;
    TCNT2 = 0;
    
    //Set LED pins as output
    DDRD |= ((1 << PD3) | (1 << PD5) | (1 << PD6));
}

int main(void) {
    //Initialize IO
	initIO();
    
    //Enable Global Interrupts
    sei();
    
    red(0);
    green(0);
    blue(0);

    //Cycle through colors
	while (1) {
        for(int i = 0; i < 255; i++){
            red(255-i);
            green(i);
            _delay_ms(1);
        }
        for(int k = 255; k >= 0; k--){
            green(k);
            blue(255-k);
            _delay_ms(1);
        }
        for(int j = 0; j < 255; j++){
            red(j);
            blue(255-j);
            _delay_ms(1);
        }

	}
	return 0; // never reached
}


ISR(PCINT1_vect){
    PORTD = 0x00;
    _delay_ms(1000);
}