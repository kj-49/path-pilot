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


#define DEBOUNCE_COUNT 5
// Prototypes
void configure_pins();
void configure();
void boot_car();

int main(void) { 

    // Initialize USART
    configure();

    move(DIRECTION_FORWARD);
    
    /*
    int obs_count = 0;
    int was_obstruction = 0;
    while (1) {
        // Check sonar reading
        if (obstruction(was_obstruction)) {
            obs_count++;
            if (obs_count < DEBOUNCE_COUNT) continue; // Skip if noise
            was_obstruction = 1;
            evade(was_obstruction);
            was_obstruction = 0; // If we return from evade we know the path is clear
        } else {
            was_obstruction = 0;
            obs_count = 0;
        }
    }
    */
}

void configure_pins() {
    
    // Configure input pins
    PORTA.DIRCLR = (1 << SONAR_ECHO_A_IN_PIN);
    
    // Configure output pins
    PORTA.DIRSET = (1 << SONAR_TRIG_A_OUT_PIN) |
        (1 << L_FOR_HI_A_OUT_PIN) | 
        (1 << L_REV_HI_A_OUT_PIN) | 
        (1 << R_FOR_HI_A_OUT_PIN) | 
        (1 << RESERVED_A_PIN) |
        (1 << L_FOR_LO_A_OUT_PIN) |
        (1 << L_REV_LO_A_OUT_PIN);
    
    PORTC.DIRSET = (1 << R_REV_HI_C_OUT_PIN);
    
    PORTD.DIRSET = (1 << R_FOR_LO_D_OUT_PIN) |
        (1 << R_REV_LO_D_OUT_PIN) |
        (1 << LED_RED_D_OUT_PIN) |
        (1 << BUZZER_D_OUT_PIN);
}

void configure() {
    configure_pins();
    
    /*
     * This sets the Internal High-Frequency Clock to 1MHz.
     * This is important for our Ultra Sonic sensor measurements and conversion.
     * This will also be the clock used for our four PWM signals.
     */
    CCP = 0xd8;
    // 1MHz for clock
    CLKCTRL.OSCHFCTRLA = 0b00000000;
    // Wait for clock to change
    while (CLKCTRL.MCLKSTATUS & 0b00000001) {
        ;
    }
    
    // Initialize PWM
    TCB0_init_pwm(OPERATING_DUTY_CYCLE);
    TCB1_init_pwm(OPERATING_DUTY_CYCLE);
    TCB2_init_pwm(OPERATING_DUTY_CYCLE);
    TCD0_init_pwm(OPERATING_DUTY_CYCLE);
    

}
