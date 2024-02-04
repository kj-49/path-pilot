
/*
 * File:   sensors.c
 * Author: ksj
 *
 * Created on January 24, 2024, 12:13 AM
 */

#include "sensors.h"
#include "avr-common.h"
#include <avr/io.h>
#include <util/delay.h>

double get_distance() {
        
    double distance = 0;
   
    /*
     * Note: By default, CLKCTRL.MCLKCTRLA is set to 0x00.
     * This means the by default, OSCHF clock is used for main clock.
     * By default, CLKCTRL.OSCHFCTRLA is set to 4MHz
     * 
     * Since we are using a 4MHz clock, we will set divider to DIV4.
     * Therefore, our TCA0.SINGLE.CNT value with be the amount of clock cycles
     * for a clock set to 1MHz. For example, TCA0.SINGLE.CNT should be 1 million after 1 second.
     * 
     * IMPORTANT: We our division is gives us enough time to execute our timer. If our timer goes past
     * TCA0.SINGLE.PER it will reset to 0x00.
     * 
     * Given our current parameters, we can effectively use the timer for timing from 0 seconds to 0.065535 seconds.
     * This should be good for ultrasonic sensor readings.
     * 
     * NOTE: Since our clock is 1Mhz, our TCA0.SINGLE.CNT will give us the clock cycles, but also the Microseconds, as they are equal in this scenario.
     */ 
    
    // FIX!!
    
        
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    // Set to max value as we will check manually
    TCA0.SINGLE.PER = 0xffff;
    while (CLKCTRL.MCLKSTATUS & 0b00000001) {
        ;
    }
    
    // send pulse
    set_pin_output_value(SONAR_TRIG_A_PIN, A, 1);
    
    // delay
    _delay_us(10);
    
    set_pin_output_value(SONAR_TRIG_A_PIN, A, 0);
    
    // wait for echo
    while(compare_pin_input_value(SONAR_ECHO_A_PIN, A, 0));
    
    // Start timer
    TCA0.SINGLE.CTRLA = 0b000000001;
    
    // start timer
    int test = 0;
    
    // wait for signal to end
    
    while(compare_pin_input_value(SONAR_ECHO_A_PIN, A, 1));
    
    // turn timer off
    
    // calculate distance
    
    // return value
    
}

void set_led(color_t color) {
    switch (color) {
        case Red:
            set_pin_output_value(LED_RED_D_PIN, A, 1);
            set_pin_output_value(LED_GREEN_D_PIN, A, 0);
            break;
        case Green:
            set_pin_output_value(LED_GREEN_D_PIN, A, 1);
            set_pin_output_value(LED_RED_D_PIN, A, 0);
            break;
        case None:
            set_pin_output_value(LED_GREEN_D_PIN, A, 0);
            set_pin_output_value(LED_GREEN_D_PIN, A, 0);
            break;
    }
}

uint16_t ms_of_sound_to_micrometers(uint16_t seconds) {
    return (seconds * 343);
}