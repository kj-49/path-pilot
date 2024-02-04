/* 
 * File:   sensors.h
 * Author: ksjam
 *
 * Created on January 24, 2024, 4:34 PM
 */

#ifndef SONIC_H
#define	SONIC_H

#include <avr/io.h>

typedef enum {
    Red,
    Green,
    None
} color_t;

uint16_t get_distance();

void set_led(color_t color);

void flicker_led(color_t color);


#endif	/* SONIC_H */

