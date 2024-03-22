/* 
 * File:   avr-common.h
 * Author: Kyle James
 *
 * Created on January 24, 2024, 12:09 PM
 */

#ifndef AVR_COMMON_H
#define	AVR_COMMON_H

/*
   ____________________________
  |                            |
--| PA0 TRIG                   |
  | PA1 ECHO                   |
  | PA2 ENA                    |
  | PA3 ENB                    |
  | PA4 IN1                    |
  | PA5 IN2                    |
  | PA6 IN3                    |
  | PA7 IN4                    |
  |                            |
  | GND                        |
  | PD1 GREEN LED              |
  | PD2 RED LED                |
  | PD3 BUZZER                 |
  | PD4                        |
  | PD5 HEADLIGHTS             |
  | PD6 PHOTOIN                |
  | PD7                        |
  |                            |
  | GND                        |
  | VDD                        |
  |____________________________|

 * 
 */


// A pins
#define SONAR_TRIG_A_OUT_PIN 0 // Sonar pulse
#define SONAR_ECHO_A_IN_PIN 1 // Sonar echo
#define LEN_A_OUT_PIN 2 // Left motor enable (PWM) (Comes out of OUT1)
#define REN_A_OUT_PIN 3 // Right motor enable (PWM) (Comes out of OUT4)
#define LFOR_A_OUT_PIN 4 // Left motor foward (IN1)
#define LBACK_A_OUT_PIN 5 // Left motor backward (IN2)
#define RFOR_A_OUT_PIN 6 // Right motor foward (IN3)
#define RBACK_A_OUT_PIN 7 // Right motor backward (IN4)

// D pins
#define PIN0_D_PIN 0 // Ground
#define LED_GREEN_D_OUT_PIN 1 
#define LED_RED_D_OUT_PIN 2 
#define BUZZER_D_OUT_PIN 3
#define HEADLIGHTS_D_OUT_PIN 4 
#define D_PIN5 5 
#define PHOTO_D_IN_PIN 6 // Need to use AC0, AINP3
#define USART_D_IN_PIN 7 // Usart transmission



#define DEBUGGING 1
#define PWM_FREQ 2000

typedef enum {
    IN,
    OUT
} pin_direction_t;

typedef enum {
    A,
    D
} port_t;

typedef struct {
    int position;
    port_t port;
    pin_direction_t direction;
} pin_t;



typedef struct {
    pin_t sonar_trig_pin;
    pin_t sonar_echo_pin;
    pin_t left_enable_pin;
    pin_t right_enable_pin;
    pin_t left_foward_pin;
    pin_t left_backward_pin;
    pin_t right_foward_pin;
    pin_t right_backward_pin;
    pin_t green_led_pin;
    pin_t red_led_pin;
    pin_t buzzer_pin;
    pin_t headlights_pin;
    pin_t photocell_in_pin;
} pinset_t;

pin_t* get_pins();


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

