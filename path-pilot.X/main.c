/*
 * File:   main.c
 * Author: ksjam
 *
 * Created on February 2, 2024, 4:07 PM
 */


#include "movement.h"
#include <avr/io.h>


// Prototypes
void configure();

int main(void) {
    
    configure();
    move(Forward);
    
    while (1) {
        // Check sonar reading
        if (obstruction()) {
            // Only set LED for initial reading of obstruction
            indicate_status(PathObstructed);
            evade();
            int a = PIN4;
        }
    }
}

void configure() {
    // Configure input pins
    PORTA.DIRCLR = SONAR_TRIG_A0PIN | SONAR_ECHO_A1PIN ;
    
    // Configure output pins
    PORTD.DIRSET = T03_D1PIN | T12_D2PIN | T47_D3PIN | T56_D4PIN;   
}
