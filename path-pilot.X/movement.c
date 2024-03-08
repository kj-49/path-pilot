/*
 * File:   movement.c
 * Author: Kyle James
 *
 * Created on January 21, 2024, 12:13 AM
 */



/* 
 * This code to reliant on an H-Bridge circuit to control the direction of a our dc motors.
             VCC
             |
  -----------|-----------
  |                      |
  |                      |
Transistor 0            Transistor 1
  |                      |
  |                      |
  ------ + MOTOR - -------
  |                      |
  |                      |
Transistor 2            Transistor 3
  |                      |
  |                      |
  -----------|-----------
             |
          Ground

 */


#include "movement.h"
#include "avr-common.h"
#include "sensors.h"
#include "communication.h"
#include <avr/io.h>

// When to count obstruction in cm.
#define DISTANCE_THRESHOLD 10

void left_wheel_set(direction_t dir);
void right_wheel_set(direction_t dir);

int obstruction() {
    if (get_distance() <= DISTANCE_THRESHOLD) {
        return 1;
    }
    return 0;
}

void stop_car() {
    // Set all transistor pins to zero.
    //PORTD.OUT &= ~(LFOR_A_OUT_PIN | LBACK_A_OUT_PIN | RFOR_A_OUT_PIN | RBACK_A_OUT_PIN);  
}

void evade() {
    stop_car();
    rotate_indefinite(CounterClockwise);
    
    while (obstruction()) {
        // Wait for a clear path to be found
    }
    stop_car();
    
    move(Forward);
}

void move(direction_t dir) {
    left_wheel_set(dir);
    right_wheel_set(dir);
}

void left_wheel_set(direction_t dir) {
    switch (dir) {
        case Forward:
            set_pwm(50, Motor_Choice_Left);
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(LBACK_A_OUT_PIN, A, 0);
            set_pin_output_value(LFOR_A_OUT_PIN, A, 1);
            break;
        case Reverse:
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(LFOR_A_OUT_PIN, A, 0);
            set_pin_output_value(LBACK_A_OUT_PIN, A, 1);
    }
}

void right_wheel_set(direction_t dir) {
    switch (dir) {
        case Forward:
            set_pwm(50, Motor_Choice_Right);
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(RBACK_A_OUT_PIN, A, 0);
            set_pin_output_value(RFOR_A_OUT_PIN, A, 1);
            break;
        case Reverse:
            // Never want all transistors on at once, so turn off first.
            set_pin_output_value(RFOR_A_OUT_PIN, A, 0);
            set_pin_output_value(RBACK_A_OUT_PIN, A, 1);
    }
}

void rotate(spindirection_t dir, float radians){
    
}

void rotate_indefinite(spindirection_t dir) {
    switch (dir) {
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

void set_pwm(int perc_duty_cycle, motor_choice_t choice) {
    
    // Set output pins MUX
    PORTMUX.TCBROUTEA = (0 << 0) | // TCB0 PWM on PA2
            (0 << 1); // TCB1 PWN on PA3
    
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    switch (choice) {
        case Motor_Choice_Both:
            TCB0.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 
            
            TCB0.CCMPL = wave_per;
            TCB0.CCMPH = pulse_width;

            TCB0.CTRLB = (1 << 4) | // Make output available on MUXed pin
                    (0x7); // Use 8-bit PWM mode
            
            TCB1.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB1.CCMPL = wave_per;
            TCB1.CCMPH = pulse_width;

            TCB1.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
            break;
        case Motor_Choice_Left:
            TCB0.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB0.CCMPL = wave_per;
            TCB0.CCMPH = pulse_width;

            TCB0.CTRLB = (1 << 4) | // Make output available on MUXed pin
                    (0x7); // Use 8-bit PWM mode
            break;
        case Motor_Choice_Right:
            TCB1.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB1.CCMPL = wave_per;
            TCB1.CCMPH = pulse_width;

            TCB1.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
            break;
    }
}