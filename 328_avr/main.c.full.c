#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "definitions.h"

//Function declarations
void init_io(void);
void init_timers(void);
void init_interrupts(void);

//global variables
volatile uint8_t enc_one_value = 128;
volatile uint8_t enc_two_value = 128;
volatile uint8_t enc_three_value = 128;

int main(void) {
    init_io();
    init_timers();
    init_interrupts();
    
    while (1)
    {
        OCR0A = enc_one_value;
        OCR0B = enc_two_value;
        OCR2B = enc_three_value;
    }
    return 0; // never reached
}

void init_io(void) {
    DDRD |= (_BV(PD6) | _BV(PD5) | _BV(PD3)); //enable output pins for LED strip
    
    ENCDDR &= ~(_BV(ENC1A_DDR) |
                _BV(ENC1B_DDR) |
                _BV(ENC2A_DDR) |
                _BV(ENC2B_DDR) |
                _BV(ENC3A_DDR) |
                _BV(ENC3B_DDR)); //setup encoder pins as input
    
    ENCPORT |= (_BV(ENC1A_PORT) |
                _BV(ENC1B_PORT) |
                _BV(ENC2A_PORT) |
                _BV(ENC2B_PORT) |
                _BV(ENC3A_PORT) |
                _BV(ENC3B_PORT));  //enable pullups
}

void init_timers(void)
{
    //Configure TIMER0
    //Fast PWM, non-inverting for A and B, no prescaler
    //  Clear OC0A/B on compare match, set on BOTTOM (non-inverting)
    //TCCR0A = 1010 XX11
    //TCCR0B = XXXX X001
    TCCR0A |= (_BV(WGM01) | _BV(WGM00)); //11
    TCCR0A = (_BV(COM0A1) | (TCCR0A & ~(_BV(COM0A0)))); //10
    TCCR0A = (_BV(COM0B1) | (TCCR0A & ~(_BV(COM0B0)))); //10
    TCCR0B = ((TCCR0B & ~(_BV(CS02) | _BV(CS01))) | _BV(CS00)); //001
    TCNT0 = 0;
    
    //Configure TIMER2
    //Fast PWM, normal port operation for A, non-inverting for B, no prescaler
    //TCCR2A = 0010 XX11
    //TCCR2B = XXXX X001
    TCCR2A |= (_BV(WGM01) | _BV(WGM00)); //11
    //TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0)); //00
    TCCR2A = (_BV(COM2B1) | (TCCR2A & ~(_BV(COM2B0)))); //10
    TCCR2B = ((TCCR2B & ~(_BV(CS02) | _BV(CS01))) | _BV(CS00)); //001
    TCNT2 = 0;
}

void init_interrupts(void)
{
    PCICR |= _BV(PCIE1); //enable PCINT1 interrupt signal
    PCMSK1 |= (_BV(ENC1A_INT) | _BV(ENC1B_INT)); //enable interrupt for knob 1
    PCMSK1 |= (_BV(ENC2A_INT) | _BV(ENC2B_INT)); //enable interrupt for knob 2
    PCMSK1 |= (_BV(ENC3A_INT) | _BV(ENC3B_INT)); //enable interrupt for knob 3
    sei(); //enable global interrupts
}

//PCINT1 interrupt
ISR(PCINT1_vect)
{
    static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t old_AB_one = 0x03; //holds state history for encoder 1
    static uint8_t old_AB_two = 0x03; //holds state history for encoder 2
    static uint8_t old_AB_three = 0x03; //holds state history for encoder 3
    static uint8_t enc_pin_history = 0;
    uint8_t changed_pins;
    int8_t inc;
    
    //capture which bits have changed since last time
    changed_pins = ENCPINS ^ enc_pin_history; //^ means XOR
    enc_pin_history = ENCPINS;
    
    if((changed_pins & _BV(ENC1A_PIN)) || (changed_pins & _BV(ENC1B_PIN)))
        //Change on Encoder 1 input
    {
        //shift old AB values left to make room for new reading
        old_AB_one <<= 2;
        
        //NOTE: next line requires A and B inputs to be on consecutive pins
        old_AB_one |= (ENCPINS & 0x03); //store current AB state
        
        //use combination of prev and curr AB as index to determine direction
        inc = enc_states[( old_AB_one & 0x0f )];
        
        //upper and lower bounds-checking to avoid wraparound/overflow
        if (enc_one_value > 250 && inc > 0) enc_one_value = 255;
        else if (enc_one_value < 5 && inc < 0) enc_one_value = 0;
        else enc_one_value += inc*4;
    }
    
    if((changed_pins & _BV(ENC2A_PIN)) || (changed_pins & _BV(ENC2B_PIN)))
        //Change on Encoder 2 input
    {
        old_AB_two <<= 2;
        old_AB_two |= ((ENCPINS>>2) & 0x03);
        inc = enc_states[( old_AB_two & 0x0f )];
        
        if (enc_two_value > 250 && inc > 0) enc_two_value = 255;
        else if (enc_two_value < 5 && inc < 0) enc_two_value = 0;
        else enc_two_value += inc*4;
    }
    
    if((changed_pins & _BV(ENC3A_PIN)) || (changed_pins & _BV(ENC3B_PIN)))
        //Change on Encoder 3 input
    {
        old_AB_three <<= 2;
        old_AB_three |= ((ENCPINS>>4) & 0x03);
        inc = enc_states[( old_AB_three & 0x0f )];
        
        if (enc_three_value > 250 && inc > 0) enc_three_value = 255;
        else if (enc_three_value < 5 && inc < 0) enc_three_value = 0;
        else enc_three_value += inc*4;
    }
}