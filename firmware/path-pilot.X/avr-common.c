
#include "avr-common.h"
#include <avr/io.h>

int compare_pin_input_value(int pin, port_t port, int value) {  
    switch (port) {
        case A:
            if (value) { // check for 1 in port
                return PORTA.IN & (1 << pin);
            } else { // compare for 0 in port
                return ~PORTA.IN & (1 << pin);
            }
            break;
        case D:
            if (value) { // check for 1 in port
                return PORTD.IN & (1 << pin);
            } else { // compare for 0 in port
                return ~PORTD.IN & (1 << pin);
            }
            break;
        default:
            return -1;
    }
}

void set_pin_output_value(int pin, port_t port, int value) {
    switch (port) {
        case A:
            if (value) {
                PORTA.OUT |= (1 << pin);
            } else {
                PORTA.OUT &= ~(1 << pin);
            }
            break;
        case D:
            if (value) {
                PORTD.OUT |= (1 << pin);
            } else {
                PORTD.OUT &= ~(1 << pin);
            }
            break;
    }
}
