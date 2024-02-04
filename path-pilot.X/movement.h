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

/*
 * Function:  obstruction 
 * --------------------
 * checks for any objects in the path of car.
 *
 * returns: returns 1 when an object is detected, and 0 otherwise.
 */
int obstruction();

/*
 * Function:  stop_car 
 * --------------------
 * disables all power to both motors.
 */
void stop_car();

/*
 * Function:  evade 
 * --------------------
 * Attempts to move car away from any obstructions to its path. Function will
 * only return once objects are no longer detected.
 */
void evade();

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

#endif	/* MOVEMENT_H */

