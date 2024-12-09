
#include "sensors.h"
#include "avr-common.h"
#include <util/delay.h>

float us_sound_to_centimeters(float us);

float get_distance() {       
   
    /*
     * Note: By default, CLKCTRL.MCLKCTRLA is set to 0x00.
     * This means that by default, OSCHF clock is used for main clock.
     * 
     * Since we are using a 1MHz clock, we will set no divider and simply use the main clock.
     * Therefore, our TCA0.SINGLE.CNT value with be the amount of clock cycles
     * for a clock set to 1MHz. For example, TCA0.SINGLE.CNT should be 1 million after 1 second.
     * 
     * IMPORTANT: We should make sure our division gives us enough time to execute our timer. If our timer goes past
     * TCA0.SINGLE.PER it will reset to 0x00.
     * 
     * Given our current parameters, we can effectively use the timer for timing from 0 seconds to 0.065535 seconds.
     * This should be good for ultrasonic sensor readings.
     * 
     * NOTE: Since our clock is 1MHz, our TCA0.SINGLE.CNT will give us the clock cycles, but also the Microseconds, as they are equal in this scenario.
     */
    
    // Set timer max to max values ~65000
    TCA0.SINGLE.PER = 0xffff;
    
    // send pulse
    set_pin_output_value(SONAR_TRIG_A_OUT_PIN, A, 1);
    // delay
    _delay_us(10);
    
    // end pulse
    set_pin_output_value(SONAR_TRIG_A_OUT_PIN, A, 0);
    // wait for echo
    while(compare_pin_input_value(SONAR_ECHO_A_IN_PIN, A, 0)) {
        ;
    }
    // start timer
    TCA0.SINGLE.CTRLA = 0b000000001;
    // wait for signal to end
    while(compare_pin_input_value(SONAR_ECHO_A_IN_PIN, A, 1));
    // capture timer count (clock cycles = microseconds)
    volatile uint16_t micros = TCA0.SINGLE.CNT;
    
    // reset timer for next check
    TCA0.SINGLE.CNT = 0;
    // turn timer off
    TCA0.SINGLE.CTRLA = 0b000000000;
    
    // calculate distance
    volatile float distance = us_sound_to_centimeters(micros/2);
    
    return distance;
}

float us_sound_to_centimeters(float us) {
    volatile float distance_cen = (us * 0.0343);
    return distance_cen;
}
