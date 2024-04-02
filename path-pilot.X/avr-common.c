/* 
 * File:   movement.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 9:43 AM
 */

#include "avr-common.h"
#include <avr/io.h>

int compare_pin_input_value(pin_t pin, int value) {  
        if (value) { // check for 1 in port
            return *(pin.port).IN & (1 << pin);
        } else { // compare for 0 in port
            return ~(*(pin.port).IN) & (1 << pin);
        }
    }
}

void set_pin_output_value(pin_t pin, int value) {
        if (value) {
            *(pin.port).OUT |= (1 << pin);
        } else {
            *(pin.port).OUT &= ~(1 << pin);
        }
    }
}
