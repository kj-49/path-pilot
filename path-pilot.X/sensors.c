
/*
 * File:   sensors.c
 * Author: Kyle James
 *
 * Created on January 24, 2024, 12:13 AM
 */

#include "sensors.h"
#include "avr-common.h"
#include <util/delay.h>

uint16_t us_sound_to_centimeters(uint16_t us);

uint16_t get_distance() {       
   
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
    volatile uint16_t distance = us_sound_to_centimeters(micros/2);
    
    return distance;
}

void set_led(color_t color) {
    switch (color) {
        case Red:
            set_pin_output_value(LED_RED_D_OUT_PIN, A, 1);
            set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 0);
            break;
        case Green:
            set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 1);
            set_pin_output_value(LED_RED_D_OUT_PIN, A, 0);
            break;
        case None:
            set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 0);
            set_pin_output_value(LED_RED_D_OUT_PIN, A, 0);
            break;
    }
}

void flicker_led(color_t color) {
    switch (color) {
        case Red:
            set_pin_output_value(LED_RED_D_OUT_PIN, A, 1);
            set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 0);
            for (int i = 0; i < 3; i++) {
                _delay_ms(250);
                set_pin_output_value(LED_RED_D_OUT_PIN, A, 0);
                _delay_ms(250);
                set_pin_output_value(LED_RED_D_OUT_PIN, A, 1);
            }
            break;
        case Green:
            set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 1);
            set_pin_output_value(LED_RED_D_OUT_PIN, A, 0);
            for (int i = 0; i < 3; i++) {
                _delay_ms(250);
                set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 0);
                _delay_ms(250);
                set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 1);
            }
            break;
        case None:
            set_pin_output_value(LED_GREEN_D_OUT_PIN, A, 0);
            set_pin_output_value(LED_RED_D_OUT_PIN, A, 0);
            break;
    }
}

uint16_t us_sound_to_centimeters(uint16_t us) {
    volatile uint16_t distance_cen = (us * 0.0343);
    return distance_cen;
}

void set_pwm(int perc_duty_cycle, motor_choice_t choice) {
    
    // Set output pins MUX
    PORTMUX.TCBROUTEA = (0 << 0) | // TCB0 PWM on PA2
            (0 << 1); // TCB1 PWN on PA3
    
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    switch (choice) {
        case Motor_Choice_Both:
            TCB0.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB0.CCMPL = wave_per;
            TCB0.CCMPH = pulse_width;

            TCB0.CTRLB = (1 << 4) | // Make output available on MUXed pin
                    (0x7); // Use 8-bit PWM mode
            
            TCB1.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB1.CCMPL = wave_per;
            TCB1.CCMPH = pulse_width;

            TCB1.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
            break;
        case Motor_Choice_Left:
            TCB0.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB0.CCMPL = wave_per;
            TCB0.CCMPH = pulse_width;

            TCB0.CTRLB = (1 << 4) | // Make output available on MUXed pin
                    (0x7); // Use 8-bit PWM mode
            break;
        case Motor_Choice_Right:
            TCB1.CTRLA = (1 << 0); // Enable timer, use DIV1 for CLK 

            TCB1.CCMPL = wave_per;
            TCB1.CCMPH = pulse_width;

            TCB1.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
            break;
    }
}
