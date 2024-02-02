/*
 * File:   movement.c
 * Author: ksj
 *
 * Created on January 21, 2024, 12:13 AM
 */

#include "movement.h"
#include "avr-common.h"
#include <avr/io.h>

void left_wheel_set(direction_t dir);
void right_wheel_set(direction_t dir);

int obstruction() {
    return 0;
}

void stop_car() {
    
    // Set all transistor pins to zero.
    PORTD.OUT &= ~(T03_D1PIN | T12_D2PIN | T47_D3PIN | T56_D4PIN);
    
}
int evade() {
    
    stop_car();
    rotate_indefinite(Clockwise);
    
    while (obstruction()) {
        // Wait
    }
    
    move(Forward);
    return 1;
    
}

void move(direction_t dir) {
    left_wheel_set(dir);
    right_wheel_set(dir);
}

void left_wheel_set(direction_t dir) {
    switch(dir) {
        case Forward:
            // Never want all transistors on at once, so turn off first.
            change_pin_output_value(T12_D2PIN, D, 0);
            change_pin_output_value(T03_D1PIN, D, 1);
            break;
        case Reverse:
            // Never want all transistors on at once, so turn off first.
            change_pin_output_value(T03_D1PIN, D, 0);
            change_pin_output_value(T12_D2PIN, D, 1);
    }
}

void right_wheel_set(direction_t dir) {
    switch(dir) {
        case Forward:
            // Never want all transistors on at once, so turn off first.
            change_pin_output_value(T56_D4PIN, D, 0);
            change_pin_output_value(T47_D3PIN, D, 1);
            break;
        case Reverse:
            // Never want all transistors on at once, so turn off first.
            change_pin_output_value(T47_D3PIN, D, 0);
            change_pin_output_value(T56_D4PIN, D, 1);
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
        case Evading:
            break;
        case PathClear:
            break;
        case PathObstructed:
            break;
    }
    
}
