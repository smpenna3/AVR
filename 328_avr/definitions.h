//
//  definitions.h
//  light_controller
//
//  Created by Peter MacLellan on 11/26/15.
//  Copyright (c) 2015 Wireless Club. All rights reserved.
//

#ifndef light_controller_definitions_h
#define light_controller_definitions_h

//Encoder Registers
#define ENCPORT PORTC
#define ENCPINS PINC
#define ENCDDR DDRC

//Encoder 1 Pins
#define ENC1A_INT PCINT8
#define ENC1A_PORT PORTC0
#define ENC1A_DDR DDC0
#define ENC1A_PIN PINC0

#define ENC1B_INT PCINT9
#define ENC1B_PORT PORTC1
#define ENC1B_DDR DDC1
#define ENC1B_PIN PINC1

//Encoder 2 Pins
#define ENC2A_INT PCINT10
#define ENC2A_PORT PORTC2
#define ENC2A_DDR DDC2
#define ENC2A_PIN PINC2

#define ENC2B_INT PCINT11
#define ENC2B_PORT PORTC3
#define ENC2B_DDR DDC3
#define ENC2B_PIN PINC3

//Encoder 3 Pins
#define ENC3A_INT PCINT12
#define ENC3A_PORT PORTC4
#define ENC3A_DDR DDC4
#define ENC3A_PIN PINC4

#define ENC3B_INT PCINT13
#define ENC3B_PORT PORTC5
#define ENC3B_DDR DDC5
#define ENC3B_PIN PINC5

#endif