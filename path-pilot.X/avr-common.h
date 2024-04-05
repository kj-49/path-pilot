/* 
 * File:   avr-common.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 12:09 PM
 */

#ifndef AVR_COMMON_H
#define	AVR_COMMON_H

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
  | PD6                        |
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
#define L_FOR_LO_A_OUT_PIN 6 //
#define L_REV_LO_A_OUT_PIN 7 //

// C pins
#define R_REV_HI_C_OUT_PIN 0 // TCB2 Output

// D pins
#define GROUND__ 0 // Ground
#define R_FOR_LO_D_OUT_PIN 1 
#define R_REV_LO_D_OUT_PIN 2 
#define LED_RED_D_OUT_PIN 3
#define BUZZER_D_OUT_PIN 4 // Ground
#define D_PIN5 5 
#define D_PIN6 6 // Need to use AC0, AINP3
#define USART_D_IN_PIN 7 // Usart transmission



#define DEBUGGING 1
#define PWM_FREQ 2000
#define OPERATING_DUTY_CYCLE 50

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

