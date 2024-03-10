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
    Forward,
    Reverse
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
    Left,
    Right
} side_t;

typedef enum {
    Motor_Choice_Left,
    Motor_Choice_Right,
    Motor_Choice_Both
} motor_choice_t;

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
 * Function:  stop_car 
 * --------------------
 * disables all power to both motors.
 */
void stop_car();

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
 * Function:  rotate 
 * --------------------
 * rotate vehicle in direction dir by degrees radians.
 * 
 * dir: direction to rotate
 * radians: degrees to rotate
 */
void rotate(spindirection_t dir, float radians);

/*
 * Function:  rotate_indefinite 
 * --------------------
 * rotate vehicle indefinitely.
 * 
 * dir: direction to rotate
 */
void rotate_indefinite(spindirection_t dir);

/*
 * Function:  indicate_status 
 * --------------------
 * sets led light to color linked to status
 * 
 * status: status of car
 */
void indicate_status(status_t status);

/*
 * Function:  set_pwm 
 * --------------------
 * sets pwm to motors
 * 
 */
void set_pwm(int perc_duty_cycle, motor_choice_t choice);

#endif	/* MOVEMENT_H */

