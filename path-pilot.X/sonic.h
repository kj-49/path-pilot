/* 
 * File:   sonic.h
 * Author: ksjam
 *
 * Created on January 24, 2024, 4:34 PM
 */

#ifndef SONIC_H
#define	SONIC_H

// Input pins on P
#define SONAR_TRIG_A0PIN 0b00000001
#define SONAR_ECHO_A1PIN 0b00000010

double get_distance();

#endif	/* SONIC_H */

