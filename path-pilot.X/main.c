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

#define OPERATING_DUTY_CYCLE 50

// Prototypes
void configure_pins();
void boot_car();

int main(void) { 

    // Initialize USART
    usart_init();
    boot_car();

    move(Foward);
    
    
    indicate_status(PathClear);
    
    while (1) {
        // Check sonar reading
        if (obstruction()) {
            //u_println("Obstruction detected.");
            // Only set LED for initial reading of obstruction
            indicate_status(PathObstructed);
            evade();
            indicate_status(PathClear);
        }
        // Experimental, could help to check less frequently.
        _delay_us(50000); // delay 50 milliseconds
    }
    
}

void configure_pins() {
    
    // Configure input pins
    PORTA.DIRCLR = (1 << SONAR_ECHO_A_IN_PIN);
    
    // Configure output pins
    PORTD.DIRSET = (1 << LEN_A_OUT_PIN) | 
        (1 << REN_A_OUT_PIN) | 
        (1 << LFOR_A_OUT_PIN) | 
        (1 << LBACK_A_OUT_PIN) |
        (1 << RFOR_A_OUT_PIN) |
        (1 << RBACK_A_OUT_PIN);
    
    PORTA.DIRSET = (1 << SONAR_TRIG_A_OUT_PIN);
    
}

void boot_car() {
    configure_pins();
    
    // Flash LED to indicate restart
    flicker_led(Green);
    
    // Start pwm
    set_pwm(OPERATING_DUTY_CYCLE, Motor_Choice_Both);
}
