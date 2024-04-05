/* 
 * File:   movement.h
 * Author: ksj
 *
 * Created on January 21, 2024, 9:43 AM
 */
#ifndef MOVEMENT_H
#define	MOVEMENT_H

#include <stdint.h>

typedef enum {
    DIRECTION_FORWARD,
    DIRECTION_REVERSE,
    DIRECTION_NONE
} direction_t;

typedef enum {
    Clockwise,
    CounterClockwise
} spindirection_t;

typedef enum {
    PathClear,
    PathObstructed
} status_t;

typedef enum {
    SIDE_LEFT,
    SIDE_RIGHT
} side_t;

typedef enum {
    Motor_Choice_Left,
    Motor_Choice_Right,
    Motor_Choice_Both
} motor_choice_t;

typedef enum {
    LEFT_WHEEL_TOP_LEFT,
    LEFT_WHEEL_TOP_RIGHT,
    LEFT_WHEEL_BOTTOM_LEFT,
    LEFT_WHEEL_BOTTOM_RIGHT,
    RIGHT_WHEEL_TOP_LEFT,
    RIGHT_WHEEL_TOP_RIGHT,
    RIGHT_WHEEL_BOTTOM_LEFT,
    RIGHT_WHEEL_BOTTOM_RIGHT
} h_bridge_gate_t;

/*
 * Function:  obstruction 
 * --------------------
 * checks for any objects in the path of car.
 *
 * was_obstruction: the current state of our application
 * 
 * returns: returns 1 when an object is detected, and 0 otherwise.
 */
int obstruction(int was_obstruction);

/*
 * Function:  evade 
 * --------------------
 * 
 * was_obstruction: the current state of our application
 * 
 * Attempts to move car away from any obstructions to its path. Function will
 * only return once objects are no longer detected.
 */
void evade(int was_obstruction);

/*
 * Function:  move 
 * --------------------
 * enables both motor in direction dir
 * 
 * dir: direction to move
 * 
 */
void move(direction_t dir);

/*
 * Function:  rotate_indefinite 
 * --------------------
 * rotate vehicle indefinitely.
 * 
 * dir: direction to rotate
 */
void rotate_indefinite(spindirection_t dir);


/*
 * Function:  left_wheel_init_pwm 
 * --------------------
 * Configures pww for left wheel, but does not enable waveform.
 * 
 * perc_duty_cycle: percentage duty cycle
 * 
 */
void left_wheel_init_pwm(int perc_duty_cycle);

/*
 * Function:  right_wheel_init_pwm 
 * --------------------
 * Configures pww for right wheel, but does not enable waveform.
 * 
 * perc_duty_cycle: percentage duty cycle
 * 
 */

void TCB0_set_duty_cycle(int perc_duty_cycle);
void TCB1_set_duty_cycle(int perc_duty_cycle);
void TCB2_set_duty_cycle(int perc_duty_cycle);
void TCD0_set_duty_cycle(int perc_duty_cycle);

/*
 * Function:  TCD0_init_pwm 
 * --------------------
 * Configures pww for TCD2, but does not enable waveform.
 * 
 * perc_duty_cycle: percentage duty cycle
 * 
 */
void turn(side_t side);

#endif	/* MOVEMENT_H */

