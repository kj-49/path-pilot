/* 
 * File:   sensors.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 4:34 PM
 */

#ifndef SENSORS_H
#define	SENSORS_H

#include <avr/io.h>
#include <avr/delay.h>

typedef enum {
    Red,
    Green,
    None
} color_t;

float get_distance();

void set_led(color_t color);

void flicker_led();




#endif	/* SENSORS_H */

