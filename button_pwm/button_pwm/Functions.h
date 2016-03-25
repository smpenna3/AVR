//
//  Functions.h
//  button_pwm
//
//  Created by Seth Penna on 3/17/16.
//  Copyright (c) 2016 Seth Penna. All rights reserved.
//

#ifndef button_pwm_Functions_h
#define button_pwm_Functions_h


void green(int intensity){
    OCR0A = (255-intensity);
}

void blue(int intensity){
    OCR0B = (255-intensity);
}

void red(int intensity){
    OCR2B = (255-intensity);
}

void alloff(){
    red(0);
    green(0);
    blue(0);
}




#endif
