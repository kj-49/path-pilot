/* 
 * File:   movement.h
 * Author: ksj
 *
 * Created on January 24, 2024, 9:43 AM
 */

#include "avr-common.h"
#include <avr/io.h>

int compare_pin_input_value(uint8_t pin, port_t port, int value) {  
    switch(port) {
        case A:
            if(value) { // check for 1 in port
                return PORTA.IN & pin;
            } else { // compare for 0 in port
                return ~PORTA.IN & pin;
            }
            break;
        case D:
            if(value) { // check for 1 in port
                return PORTD.IN & pin;
            } else { // compare for 0 in port
                return ~PORTD.IN & pin;
            }
            break;
        default:
            return -1;
    }
}

void change_pin_output_value(uint8_t pin, port_t port, int value) {
    switch(port) {
        case A:
            if(value) {
                PORTA.OUT |= pin;
            } else {
                PORTA.OUT &= ~pin;
            }
            break;
        case D:
            if(value) {
                PORTD.OUT |= pin;
            } else {
                PORTD.OUT &= ~pin;
            }
            break;
    }
}
