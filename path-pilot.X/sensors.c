
/*
 * File:   sensors.c
 * Author: ksj
 *
 * Created on January 24, 2024, 12:13 AM
 */

#include "sensors.h"
#include "avr-common.h"
#include <avr/io.h>
#include <util/delay.h>

double get_distance() {
        
    double distance = 0;
    
    // send pulse
    change_pin_output_value(SONAR_TRIG_A_PIN, A, 1);
    
    // delay
    _delay_us(10);
    
    // wait for echo
    while(compare_pin_input_value(SONAR_ECHO_A_PIN, A, 0));
    
    // start timer
    
    // wait for signal to end
    
    while(compare_pin_input_value(SONAR_ECHO_A_PIN, A, 1));
    
    // turn timer off
    
    // calculate distance
    
    // return value
    
}

void set_led(color_t color) {
    switch (color) {
        case Red:
            set_pin_output_value(LED_RED_D_PIN, A, 1);
            set_pin_output_value(LED_GREEN_D_PIN, A, 0);
            break;
        case Green:
            set_pin_output_value(LED_GREEN_D_PIN, A, 1);
            set_pin_output_value(LED_RED_D_PIN, A, 0);
            break;
        case None:
            set_pin_output_value(LED_GREEN_D_PIN, A, 0);
            set_pin_output_value(LED_GREEN_D_PIN, A, 0);
            break;
    }
}