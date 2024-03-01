/* 
 * File:   avr-common.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 12:09 PM
 */

#ifndef AVR_COMMON_H
#define	AVR_COMMON_H

// Available AVR pins

// D pins
#define PIN0_D_PIN 0 // Ground
#define LEN_D_OUT_PIN 1 // Left motor enable
#define REN_D_OUT_PIN 2 // Right motor enable
#define LFOR_D_OUT_PIN 3 // Left motor foward
#define LBACK_D_OUT_PIN 4 // Left motor backward
#define RFOR_RED_D_OUT_PIN 5 // Right motor foward
#define RBACK_GREEN_D_OUT_PIN 6 // Right motor backward
#define USART_D_OUT_PIN 7 // Usart transmission

// A pins
#define SONAR_TRIG_A_OUT_PIN 0 // Sonar pulse
#define SONAR_ECHO_A_IN_PIN 1 // Sonar echo
#define PIN2_A_PIN 2
#define PIN3_A_PIN 3
#define PIN4_A_PIN 4
#define PIN5_A_PIN 5
#define PIN6_A_PIN 6
#define USART_D_IN_PIN 7 // Usart reception

#define DEBUGGING 1

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

