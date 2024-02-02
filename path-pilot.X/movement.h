/* 
 * File:   movement.h
 * Author: ksj
 *
 * Created on January 21, 2024, 9:43 AM
 */
#ifndef MOVEMENT_H
#define	MOVEMENT_H

#include <stdint.h>

// Input pins on P
#define SONAR_TRIG_A0PIN 0b00000001
#define SONAR_ECHO_A1PIN 0b00000010

// Output pins on D
#define T03_D1PIN 0b00000010 // Forward left tire
#define T12_D2PIN 0b00000100 // Reverse left tire
#define T47_D3PIN 0b00001000 // Forward right tire
#define T56_D4PIN 0b00010000 // Reverse right tire



typedef enum {
    Forward,
    Reverse
} direction_t;

typedef enum {
    Clockwise,
    CounterClockwise
} spindirection_t;

typedef enum {
    Evading,
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
 * attempts to move car away from any obstructions to its path.
 *  
 * returns: if the car manages to find a new path 1 is returned, if not 0 is returned.
 */
int evade();

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

