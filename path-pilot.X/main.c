/*
 * File:   main.c
 * Author: Kyle James
 *
 * Created on February 2, 2024, 4:07 PM
 */


#include "movement.h"
#include "sensors.h"
#include "avr-common.h"
#include "communication.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define OPERATING_DUTY_CYCLE 70
#define DEBOUNCE_COUNT 20
// Prototypes
void configure_pins();
void boot_car();

int main(void) { 

    // Initialize USART
    usart_init();
    boot_car();

    move(Forward);
    
    indicate_status(PathClear);
    
    int obs_count = 0;
    int was_obstruction = 0;
    while (1) {
        // Check sonar reading
        if (obstruction(was_obstruction)) {
            obs_count++;
            if (!(obs_count > DEBOUNCE_COUNT)) continue; // Skip if noise
            was_obstruction = 1;
            
            indicate_status(PathObstructed);
            evade(was_obstruction);
            was_obstruction = 0; // If we return from evade we know the path is clear
            
            indicate_status(PathClear);
        } else {
            was_obstruction = 0;
            obs_count = 0;
        }
    }
    
}

void configure_pins() {
    
    // Configure input pins
    PORTA.DIRCLR = (1 << SONAR_ECHO_A_IN_PIN);
    
    // Configure output pins
    PORTA.DIRSET = (1 << LEN_A_OUT_PIN) | 
        (1 << REN_A_OUT_PIN) | 
        (1 << LFOR_A_OUT_PIN) | 
        (1 << LBACK_A_OUT_PIN) |
        (1 << RFOR_A_OUT_PIN) |
        (1 << RBACK_A_OUT_PIN);
    
    PORTD.DIRSET = (1 << LED_GREEN_D_OUT_PIN) |
        (1 << LED_RED_D_OUT_PIN) |
        (1 << BUZZER_D_OUT_PIN);
 
    
    PORTA.DIRSET = (1 << SONAR_TRIG_A_OUT_PIN);
    
}

void boot_car() {
    configure_pins();
    
    // Flash LED to indicate restart
    flicker_led(Green);
    
    // Start pwm
    set_pwm(OPERATING_DUTY_CYCLE, Motor_Choice_Both);
}
