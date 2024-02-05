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

// Prototypes
void configure_pins();
void boot_car();

int main(void) { 
    
    boot_car();
    move(Forward);
    while (1) {
        // Check sonar reading
        if (obstruction()) {
            // Only set LED for initial reading of obstruction
            indicate_status(PathObstructed);
            evade();
            indicate_status(PathClear);
        }
    }
}

void configure_pins() {
    
    // Configure input pins
    PORTA.DIRCLR = (1 << SONAR_ECHO_A_IN_PIN);
    
    // Configure output pins
    PORTD.DIRSET = (1 << T03_D_OUT_PIN) | 
        (1 << T12_D_OUT_PIN) | 
        (1 << T47_D_OUT_PIN) | 
        (1 << T56_D_OUT_PIN) |
        (1 << LED_RED_D_OUT_PIN) |
        (1 << LED_GREEN_D_OUT_PIN);
    
    PORTA.DIRSET = (1 << SONAR_TRIG_A_OUT_PIN);
    
}

void boot_car() {
    configure_pins();
    
    // Initialize USART
    usart_init();
    
    // Flash LED to indicate restart
    flicker_led(Green);
}
