/* 
 * File:   avr-common.h
 * Author: ksjam
 *
 * Created on January 24, 2024, 12:09 PM
 */

#ifndef AVR_COMMON_H
#define	AVR_COMMON_H

// Available AVR pins

// D pins
#define PIN0_D_PIN 0 // Ground
#define T03_D_OUT_PIN 1 // Forward left tire
#define T12_D_OUT_PIN 2 // Reverse left tire
#define T47_D_OUT_PIN 3 // Forward right tire
#define T56_D_OUT_PIN 4 // Reverse right tire
#define LED_RED_D_OUT_PIN 5 // Red LED
#define LED_GREEN_D_OUT_PIN 6 // Green LED
#define PIN7_D_PIN 7

// A pins
#define SONAR_TRIG_A_OUT_PIN 0 // Sonar pulse
#define SONAR_ECHO_A_IN_PIN 1
#define PIN2_A_PIN 2
#define PIN3_A_PIN 3
#define PIN4_A_PIN 4
#define PIN5_A_PIN 5
#define PIN6_A_PIN 6
#define PIN7_A_PIN 7

typedef enum {
    A,
    D
} port_t;

/*
 * Function:  set_pin_output_value 
 * --------------------
 * changes state of a single pin to value
 * 
 * pin: 8-bit binary int with the pin to change set to 1, and all others set to 0
 * port: the port the pin belongs to
 * value: the value to change single pin, (1 or 0)
 * 
 */
void set_pin_output_value(int pin, port_t port, int value);

/*
 * Function:  compare_pin_input_value 
 * --------------------
 * checks if the state of the pin matches value
 * 
 * pin: 8-bit binary int with the pin to change set to 1, and all others set to 0
 * port: the port the pin belongs to
 * value: the value we want to compare to pin value.
 * 
 * returns: returns -1 if an error has occurred, 1 if the pin state is the same as value, 0 otherwise.
 */
int compare_pin_input_value(int pin, port_t port, int value);



#endif	/* AVR_COMMON_H */

