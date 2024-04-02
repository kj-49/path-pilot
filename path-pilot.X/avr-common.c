/* 
 * File:   movement.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 9:43 AM
 */

#include "avr-common.h"
#include <avr/io.h>

<<<<<<< HEAD
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
=======

pin_t sonar_trig_pin = {
    0,
    A,
    OUT
};
pin_t sonar_echo_pin = {
    1,
    A,
    IN
};
pin_t left_enable_pin = {
    2,
    A,
    OUT
};
pin_t right_enable_pin = {
    3,
    A,
    OUT
};
pin_t left_forward_pin = {
    4,
    A,
    OUT
};
pin_t left_backward_pin = {
    5,
    A,
    OUT
};
pin_t right_foward_pin = {
    6,
    A,
    OUT
};
pin_t right_backward_pin = {
    7,
    A,
    OUT
};
pin_t green_led_pin = {
    1,
    D,
    OUT
};
pin_t red_led_pin = {
    2,
    D,
    OUT
};
pin_t buzzer_led_pin = {
    3,
    D,
    OUT
};
pin_t headlights_led_pin = {
    4,
    D,
    OUT
};
pin_t photocell_in_pin = {
    6,
    D,
    IN
};

pin_t* get_pins() {
    volatile pin_t pins[] = {
        sonar_trig_pin,
        sonar_echo_pin,
        left_enable_pin,
        right_enable_pin,
        left_forward_pin,
        left_backward_pin,
        right_foward_pin,
        right_backward_pin,
        green_led_pin,
        red_led_pin,
        buzzer_led_pin,
        headlights_led_pin,
        photocell_in_pin
    };
    return pins;
}

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
>>>>>>> cd660f2503dfb4a7556db9e0daf5db87ba636e80
    }
}
