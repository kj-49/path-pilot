/*
 * File:   main.c
 * Author: ksjam
 *
 * Created on February 2, 2024, 4:07 PM
 */


#include "movement.h"
#include "sensors.h"

#include <avr/io.h>


// Prototypes
void configure_pins();

int main(void) {
    
    configure_pins();
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
    PORTA.DIRCLR = (1 << SONAR_ECHO_A_PIN);
    
    // Configure output pins
    PORTD.DIRSET = (1 << T03_D_PIN) | 
        (1 << T12_D_PIN) | 
        (1 << T47_D_PIN) | 
        (1 << T56_D_PIN) |
        (1 << LED_RED_D_PIN) |
        (1 << LED_GREEN_D_PIN) |
        (1 << SONAR_TRIG_A_PIN);
}