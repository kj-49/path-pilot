/* 
 * File:   avr-common.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 12:09 PM
 */

#ifndef AVR_COMMON_H
#define	AVR_COMMON_H

#include <avr/io.h>
#include <avr/ioavr128db28.h>

/* 
 * This code to reliant on an H-Bridge circuit to control the direction of a our dc motors.
             VCC
             |
  -----------|-----------
  |                      |
  |                      |
Transistor 0            Transistor 1
  |                      |
  |                      |
  ------ + MOTOR - -------
  |                      |
  |                      |
Transistor 2            Transistor 3
  |                      |
  |                      |
  -----------|-----------
             |
          Ground

 */


/*
   ____________________________
  |                            |
--| PA0 TRIG                   |
  | PA1 ECHO                   |
  | PA2 L FORWARD HIGH GATE    |
  | PA3 L REVERSE HIGH GATE    |
  | PA4 R FORWARD HIGH GATE    |
  | PA5 !RESERVED              |
  | PA6 L FORWARD LOW GATE     |
  | PA7 L REVERSE LOW GATE     |
  |                            |
  | PC0 R REVERSE HIGH GATE    |
  |                            |
  | GND                        |
  | PD1 R FORWARD LOW GATE     |
  | PD2 R REVERSE LOW GATE     |
  | PD3 BUZZER                 |
  | PD4                        |
  | PD5 HEADLIGHTS             |
  | PD6 PHOTOIN                |
  | PD7                        |
  |                            |
  | GND                        |
  | VDD                        |
  |____________________________| 
 */

/*
 * Available pins for Timers:
 * TCB0: PA2
 * TCB1: PA3
 * TCB2: PC0
 * TCD0: PA4 (W0A), PA5 (W0B)
 */


// A pins
#define SONAR_TRIG_A_OUT_PIN 0 // Sonar pulse
#define SONAR_ECHO_A_IN_PIN 1 // Sonar echo
#define L_FOR_HI_A_OUT_PIN 2 // TCB0 Output
#define L_REV_HI_A_OUT_PIN 3 // TCB1 Output
#define R_FOR_HI_A_OUT_PIN 4 // TCD0 W0 Output
#define RESERVED_A_PIN 5 // TCD W1 Output
#define L_FOR_LO_A_OUT_PIN 6 // Right motor foward (IN3)
#define L_REV_LO_A_OUT_PIN 7 // Right motor backward (IN4)

// C pins
#define R_REV_HI_C_OUT_PIN 0 // TCB2 Output

// D pins
#define R_FOR_LO_D_OUT_PIN 0 // Ground
#define R_REV_LO_D_OUT_PIN 1 
#define LED_RED_D_OUT_PIN 2 
#define BUZZER_D_OUT_PIN 3
#define D_PIN4 4 
#define D_PIN5 5 
#define D_PIN6 6 // Need to use AC0, AINP3
#define USART_D_IN_PIN 7 // Usart transmission



#define DEBUGGING 1
#define PWM_FREQ 2000

// Enum to represent pin direction
typedef enum {
    PIN_DIRECTION_IN,
    PIN_DIRECTION_OUT
} pin_direction_t;

// Define the Pin structure
typedef struct {
    volatile PORT_t *port;
    uint8_t pin;
    pin_direction_t direction; // Indicates whether the pin is an input or output
} pin_t;

// Define constant pins for A port
const pin_t SONAR_TRIG = {&PORTA, SONAR_TRIG_A_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t SONAR_ECHO = {&PORTA, SONAR_ECHO_A_IN_PIN, PIN_DIRECTION_IN};
const pin_t L_FOR_HI = {&PORTA, L_FOR_HI_A_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t L_REV_HI = {&PORTA, L_REV_HI_A_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t R_FOR_HI = {&PORTA, R_FOR_HI_A_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t RESERVED_A = {&PORTA, RESERVED_A_PIN, PIN_DIRECTION_OUT};
const pin_t L_FOR_LO = {&PORTA, L_FOR_LO_A_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t L_REV_LO = {&PORTA, L_REV_LO_A_OUT_PIN, PIN_DIRECTION_OUT};

// Define constant pins for C port
const pin_t R_REV_HI = {&PORTC, R_REV_HI_C_OUT_PIN, PIN_DIRECTION_OUT};

// Define constant pins for D port
const pin_t R_FOR_LO = {&PORTD, R_FOR_LO_D_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t R_REV_LO = {&PORTD, R_REV_LO_D_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t LED_RED = {&PORTD, LED_RED_D_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t BUZZER = {&PORTD, BUZZER_D_OUT_PIN, PIN_DIRECTION_OUT};
const pin_t USART = {&PORTD, USART_D_IN_PIN, PIN_DIRECTION_IN};

#define DEBUGGING 1
#define PWM_FREQ 2000

typedef enum {
    A,
    D
} port_t;

/*
 * Function:  set_pin_output_value 
 * --------------------
 * changes state of a single pin to value
 * 
 * pin: the pin
 * value: the value to change single pin, (1 or 0)
 * 
 */
void set_pin_output_value(pin_t pin, int value);

/*
 * Function:  compare_pin_input_value 
 * --------------------
 * checks if the state of the pin matches value
 * 
 * pin: the pin
 * value: the value we want to compare to pin value.
 * 
 * returns: 1 if the pin state is the same as value, 0 otherwise.
 */
int compare_pin_input_value(pin_t pin, int value);

*pins



#endif	/* AVR_COMMON_H */

