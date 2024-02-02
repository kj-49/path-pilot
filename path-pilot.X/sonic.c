
/*
 * File:   sonic.c
 * Author: ksj
 *
 * Created on January 24, 2024, 12:13 AM
 */

#include "sonic.h"
#include "avr-common.h"
#include <avr/io.h>

double get_distance() {
        
    double distance = 0;
    
    // send pulse
    change_pin_output_value(SONAR_TRIG_A0PIN, A, 1);
    
    // delay
    __delay_us(10);
    
    // wait for echo
    while(compare_pin_input_value(SONAR_ECHO_A1PIN, A, 0));
    
    // start timer
    
    // wait for signal to end
    
    while(compare_pin_input_value(SONAR_ECHO_A1PIN, A, 1));
    
    // turn timer off
    
    // calculate distance
    
    // return value
    
}