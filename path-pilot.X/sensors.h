/* 
 * File:   sensors.h
 * Author: ksjam
 *
 * Created on January 24, 2024, 4:34 PM
 */

#ifndef SONIC_H
#define	SONIC_H

// Input pins on P
#define SONAR_TRIG_A_PIN 0
#define SONAR_ECHO_A_PIN 1

// LED pins
#define LED_RED_D_PIN 5
#define LED_GREEN_D_PIN 6

typedef enum {
    Red,
    Green,
    None
} color_t;

double get_distance();

void set_led(color_t color);



#endif	/* SONIC_H */

