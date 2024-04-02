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

#define OPERATING_DUTY_CYCLE 99
#define DEBOUNCE_COUNT 20
// Prototypes
void configure_pins();
void configure();
void boot_car();

int main(void) {
    
    volatile pin_t *pins = get_pins();
    volatile pin_t pin = *(pins + 2);
    
    
    // Initialize USART
    configure();
    move(Forward);
    
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
    
}

void configure_pins() {
    const size_t num_pins = sizeof(pins) / sizeof(pins[0]);
    
    for (size_t i = 0; i < num_pins; ++i) {
        if (pins[i].direction == PIN_DIRECTION_OUT) {
            // Set pin as output
            *(pins[i].port).OUT |= pins[i].pin;
        } else {
            // Set pin as input
            *(pins[i].port).IN |= pins[i].pin;
        }
    }
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
    
    // Initalize PWM
    TCB0_init_pwm(50);
    TCB1_init_pwm(50);
    TCB2_init_pwm(50);
    TCD0_init_pwm(50);

}
