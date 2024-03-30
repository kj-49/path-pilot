/*
 * File:   movement.c
 * Author: Kyle James
 *
 * Created on January 21, 2024, 12:13 AM
 */


#include "movement.h"
#include "avr-common.h"
#include "sensors.h"
#include "communication.h"
#include <avr/io.h>

// When to count obstruction in cm.
#define STOP_THRESHOLD 15 // Stop if below 10
#define GO_THRESHOLD 20 // Go if above 12

void left_wheel_set(direction_t dir);
void right_wheel_set(direction_t dir);
void set_TCB0(int state);
void set_TCB1(int state);
void set_TCB2(int state);
void set_TCD0(int state);
void set_gate(h_bridge_gate_t gate, int value);

int obstruction(int was_obstruction) {
    float dist = get_distance();
    /*
     * To change application state, we must be either over the GO_THRESHOLD
     * or under the STOP_THRESHOLD. The reason these number are not the same
     * is to avoid metastability where a sensor reading maybe vary ~1cm and
     * flicker our application state. This way, our app either meets these
     * requirements, or the state remains unchanged.
     */
    if (dist <= STOP_THRESHOLD) {
        return 1;
    } else if (dist > GO_THRESHOLD) {
        return 0;
    }
    return was_obstruction;
}

void stop_car() {  

}

void evade(int was_obstruction) {
    stop_car();
    rotate_indefinite(CounterClockwise);
    
    int safe_count = 0;
    
    while (safe_count < 20) {
        // Wait for a clear path to be found
        if (!obstruction(was_obstruction)) {
            safe_count++;
        } else {
            safe_count = 0;
        }
    }
    stop_car();
    
    move(Forward);
}

void move(direction_t dir) {
    left_wheel_set(dir);
    right_wheel_set(dir);
}

void left_wheel_set(direction_t dir) {
    switch (dir) {
        case Forward:
            // Turn off reverse gates
            set_gate(LEFT_WHEEL_TOP_RIGHT, 0);
            set_gate(LEFT_WHEEL_BOTTOM_LEFT, 0);
            _delay_ms(500);
            // Turn on forward gates
            set_gate(LEFT_WHEEL_TOP_LEFT, 1);
            set_gate(LEFT_WHEEL_BOTTOM_RIGHT, 1);
            break;
        case Reverse:
            // Turn off forward gates
            set_gate(LEFT_WHEEL_TOP_LEFT, 0);
            set_gate(LEFT_WHEEL_BOTTOM_RIGHT, 0);
            _delay_ms(500);
            // Turn on reverse gates
            set_gate(LEFT_WHEEL_TOP_RIGHT, 1);
            set_gate(LEFT_WHEEL_BOTTOM_LEFT, 1);   
    }
}

void right_wheel_set(direction_t dir) {
        switch (dir) {
            case Forward:
                // Turn off reverse gates
                set_gate(RIGHT_WHEEL_TOP_RIGHT, 0);
                set_gate(RIGHT_WHEEL_BOTTOM_LEFT, 0);
                _delay_ms(500);
                // Turn on forward gates
                set_gate(RIGHT_WHEEL_TOP_LEFT, 1);
                set_gate(RIGHT_WHEEL_BOTTOM_RIGHT, 1);
                break;
            case Reverse:
                // Turn off forward gates
                set_gate(RIGHT_WHEEL_TOP_LEFT, 0);
                set_gate(RIGHT_WHEEL_BOTTOM_RIGHT, 0);
                _delay_ms(500);
                // Turn on reverse gates
                set_gate(RIGHT_WHEEL_TOP_RIGHT, 1);
                set_gate(RIGHT_WHEEL_BOTTOM_LEFT, 1);   
        }
}

void rotate(spindirection_t dir, float radians){
    
}

void rotate_indefinite(spindirection_t dir) {
    switch (dir) {
        case Clockwise:
            left_wheel_set(Forward);
            right_wheel_set(Reverse);
            break;
        case CounterClockwise:
            left_wheel_set(Reverse);
            right_wheel_set(Forward);
            break;
    }
}

void TCB0_init_pwm(int perc_duty_cycle) {
    
    // Set output pins MUX
    PORTMUX.TCBROUTEA &= ~(1 << 0); // TCB0 PWM on PA2
    
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);

    TCB0.CTRLA = (0 << 0); // Disable for now timer, use DIV1 for CLK 

    TCB0.CCMPL = wave_per;
    TCB0.CCMPH = pulse_width;

    TCB0.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM modee

}

void TCB1_init_pwm(int perc_duty_cycle){
    // Set output pins MUX
    PORTMUX.TCBROUTEA &= ~(1 << 1); // TCB1 PWM on PA3
    
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    TCB1.CTRLA = (0 << 0); // Disable for now timer, use DIV1 for CLK 

    TCB1.CCMPL = wave_per;
    TCB1.CCMPH = pulse_width;

    TCB1.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
}

void TCB2_init_pwm(int perc_duty_cycle){
    // Set output pins MUX
    PORTMUX.TCBROUTEA &= ~(1 << 2); // TCB1 PWM on PA3
    
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    TCB2.CTRLA = (0 << 0); // Disable for now timer, use DIV1 for CLK 

    TCB2.CCMPL = wave_per;
    TCB2.CCMPH = pulse_width;

    TCB2.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
}

void TCD0_init_pwm(int perc_duty_cycle){
    TCD0.CTRLB |= 0x00; // Use one ramp mode

    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    TCD0.CMPASET = 0x00;
    TCD0.CMPACLR = pulse_width;
       
    TCD0.CMPBSET = 0x00;
    TCD0.CMPBCLR = wave_per;
    
    TCD0.FAULTCTRL = (1 << 4) | // CMPA Enable
            (1 << 1) | // CMPA Value
            (1 << 5) | // CMPB Enable
            (1 << 2); // CMPB Value
    
    // Wait for TCD to be ready
    while (!(TCD0.STATUS & (1 << 1))) {
        ;
    }
    
    // Set OSCHF as input clock
    TCD0.CTRLA &= ~((1 << 5) | (1 << 6));
}

void set_TCB0(int state) {
    if (state) {
        TCB0.CTRLA |= (1 << 1); // Enable pwm waveform
    } else {
        TCB0.CTRLA &= ~(1 << 1); // Disable pwm waveform
    }
}

void set_TCB1(int state) {
    if (state) {
        TCB1.CTRLA |= (1 << 1); // Enable pwm waveform
    } else {
        TCB1.CTRLA &= ~(1 << 1); // Disable pwm waveform
    }
}

void set_TCB2(int state) {
    if (state) {
        TCB2.CTRLA |= (1 << 1); // Enable pwm waveform
    } else {
        TCB2.CTRLA &= ~(1 << 1); // Disable pwm waveform
    }
}


void set_TCD0(int state) {
    if (state) {
        TCD0.CTRLA |= (1 << 1); // Enable pwm waveform
    } else {
        TCD0.CTRLA &= ~(1 << 1); // Disable pwm waveform
    }
}

void set_gate(h_bridge_gate_t gate, int value) {
    switch (gate) {
        case LEFT_WHEEL_TOP_LEFT:
            set_TCB0(value);
            break;
        case LEFT_WHEEL_TOP_RIGHT:
            set_TCB1(value);
            break;
        case LEFT_WHEEL_BOTTOM_LEFT:
            set_pin_output_value(L_REV_LO_A_OUT_PIN, A, value);
            break;
        case LEFT_WHEEL_BOTTOM_RIGHT:
            set_pin_output_value(L_FOR_LO_A_OUT_PIN, A, value);
            break;
        case RIGHT_WHEEL_TOP_LEFT:
            set_TCB2(value);
            break;
        case RIGHT_WHEEL_TOP_RIGHT:
            set_TCD0(value);
            break;
        case RIGHT_WHEEL_BOTTOM_LEFT:
            set_pin_output_value(R_REV_LO_D_OUT_PIN, D, value);
            break;
        case RIGHT_WHEEL_BOTTOM_RIGHT:
            set_pin_output_value(R_FOR_LO_D_OUT_PIN, D, value);
            break;
    }
}