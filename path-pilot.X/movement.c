/*
 * File:   movement.c
 * Author: ksj
 *
 * Created on January 21, 2024, 12:13 AM
 */

#include "movement.h"
#include "avr-common.h"
#include "sensors.h"
#include <avr/io.h>

void left_wheel_set(direction_t dir);
void right_wheel_set(direction_t dir);

int obstruction() {
    return 0;
}

void stop_car() {
    
    // Set all transistor pins to zero.
    PORTD.OUT &= ~(T03_D_PIN | T12_D_PIN | T47_D_PIN | T56_D_PIN);
    
}

void evade() {
    stop_car();
    rotate_indefinite(Clockwise);
    
    while (obstruction()) {
        // Wait for a clear path to be found
    }
    
    move(Forward);
}

void move(direction_t dir) {
    left_wheel_set(dir);
    right_wheel_set(dir);
}

void left_wheel_set(direction_t dir) {
    switch(dir) {
        case Forward:
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(T12_D_PIN, D, 0);
            set_pin_output_value(T03_D_PIN, D, 1);
            break;
        case Reverse:
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(T03_D_PIN, D, 0);
            set_pin_output_value(T12_D_PIN, D, 1);
    }
}

void right_wheel_set(direction_t dir) {
    switch(dir) {
        case Forward:
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(T56_D_PIN, D, 0);
            set_pin_output_value(T47_D_PIN, D, 1);
            break;
        case Reverse:
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(T47_D_PIN, D, 0);
            set_pin_output_value(T56_D_PIN, D, 1);
    }
}

void rotate(spindirection_t dir, float radians){
    
}

void rotate_indefinite(spindirection_t dir) {
    switch (dir){
        case Clockwise:
            left_wheel_set(Forward);
            right_wheel_set(Reverse);
            break;
        case CounterClockwise:
            left_wheel_set(Reverse);
            right_wheel_set(Forward);
            break;
    }
}
void indicate_status(status_t status) {
    switch (status) {
        case PathClear:
            set_led(Green);
            break;
        case PathObstructed:
            set_led(Red);
            break;
    }
}
