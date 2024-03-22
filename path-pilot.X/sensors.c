
/*
 * File:   sensors.c
 * Author: Kyle James
 *
 * Created on January 24, 2024, 12:13 AM
 */

#include "sensors.h"
#include "avr-common.h"
#include <util/delay.h>

float us_sound_to_centimeters(float us);
int photo_changed();
int in_darkness();

float get_distance() {       
   
    /*
     * Note: By default, CLKCTRL.MCLKCTRLA is set to 0x00.
     * This means that by default, OSCHF clock is used for main clock.
     * 
     * Since we are using a 1MHz clock, we will set no divider and simply use the main clock.
     * Therefore, our TCA0.SINGLE.CNT value with be the amount of clock cycles
     * for a clock set to 1MHz. For example, TCA0.SINGLE.CNT should be 1 million after 1 second.
     * 
     * IMPORTANT: We should make sure our division is gives us enough time to execute our timer. If our timer goes past
     * TCA0.SINGLE.PER it will reset to 0x00.
     * 
     * Given our current parameters, we can effectively use the timer for timing from 0 seconds to 0.065535 seconds.
     * This should be good for ultrasonic sensor readings.
     * 
     * NOTE: Since our clock is 1MHz, our TCA0.SINGLE.CNT will give us the clock cycles, but also the Microseconds, as they are equal in this scenario.
     */
       
    CCP = 0xd8;
    // 1MHz for clock
    CLKCTRL.OSCHFCTRLA = 0b00000000;
    // Set timer max to max values ~65000
    TCA0.SINGLE.PER = 0xffff;
    // Wait for clock to change
    while (CLKCTRL.MCLKSTATUS & 0b00000001) {
        ;
    }
    
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

void set_led(color_t color) {
    switch (color) {
        case Red:
            set_pin_output_value(LED_RED_D_OUT_PIN, D, 1);
            set_pin_output_value(LED_GREEN_D_OUT_PIN, D, 0);
            break;
        case Green:
            set_pin_output_value(LED_GREEN_D_OUT_PIN, D, 1);
            set_pin_output_value(LED_RED_D_OUT_PIN, D, 0);
            break;
        case None:
            set_pin_output_value(LED_GREEN_D_OUT_PIN, D, 0);
            set_pin_output_value(LED_RED_D_OUT_PIN, D, 0);
            break;
    }
}

void flicker_led() {
    set_pin_output_value(LED_RED_D_OUT_PIN, D, 1);
    set_pin_output_value(LED_GREEN_D_OUT_PIN, D, 0);
    for (int i = 0; i < 2; i++) {
        _delay_ms(1000);
        set_pin_output_value(LED_RED_D_OUT_PIN, D, 0);
        set_pin_output_value(BUZZER_D_OUT_PIN, D, 1);
        _delay_ms(1000);
        set_pin_output_value(LED_RED_D_OUT_PIN, D, 1);
        set_pin_output_value(BUZZER_D_OUT_PIN, D, 0);
    }
    _delay_ms(1000);
    set_pin_output_value(LED_GREEN_D_OUT_PIN, D, 1);
}

float us_sound_to_centimeters(float us) {
    volatile float distance_cen = (us * 0.0343);
    return distance_cen;
}

void configure_ac() {
    // Enable global interrupts.
    SREG = 0b10000000;
    
    // Enable AC and set Medium Hysteresis
    AC0.CTRLA = 0b00000111;
    
    /*
     * To use PD6 on AC0, we need AINP3
     */
    AC0.MUXCTRL = (0x3 << 3) | // Set AINP3 for +
            (0 << 0x3); // Set DACREF for -
    
    // Use VDD as reference
    VREF.ACREF = 0b00000101;
    
    // Set DACREF to 128.
    /*
     * DACREF is a variable in the formula Vdacref = (DACREF/256) * Vref
     * Vref is set in VREF.ACREF
     * Vdacref (should be 2.5v) is the actual value which PD6 will be compared to.
     */
    AC0.DACREF = 0b10000000;
    
    AC0.INTCTRL = (0x1 << 0) | // Enabled AC interrupt. Will be triggered when CMPIF bit in AC0.STATUS is set.
            (0x0 << 4); // Generate interrupt on Positive & Negative crosses
    /*
     * See check output: bit 0 of AC0.STATUS will be 1 when edge is crossed in any direction (2.5v).
     * To tell which way we have crossed:
     * Bit 4 of AC0.STATUS is CMPSTATE bit. It is 1 when High
     * and 0 when low.
     */
}

void handle_headlights() {
    if (photo_changed()) {
        int new_io_value = in_darkness();
        set_pin_output_value(HEADLIGHTS_D_OUT_PIN, D, new_io_value);
    }
    photo_changed();
}

int photo_changed() {
    if (AC0.STATUS) {
    }
    if (AC0.STATUS & (1 << 0)) {
        AC0.STATUS = 1;
        return 1;
    }
    return 0;
}

/*
 * For our photo resistor --
 * Bright light: <= ~1kohm
 * Room light: ~1kohm - ~75kohm
 * Darkness: >= 75kohm (up to 350kohm+)
 * 
 * For 5.1kohm:
 * Normal Vin > 2.5, Dark Vin < 1.3
 */
int in_darkness() {
    if (AC0.STATUS) {
    }
    if (AC0.STATUS & (1 << 4)) { // if comparator crossed to positive
        return 0;
    } else { // comparator crossed to negative
        return 1;
    }
}