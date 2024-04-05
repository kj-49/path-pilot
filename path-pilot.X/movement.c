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
#include "audio.h"
#include <avr/io.h>

// When to count obstruction in cm.
#define STOP_THRESHOLD 15 // Stop if below 10
#define GO_THRESHOLD 20 // Go if above 12
#define BUZZER_INTERVAL_MS 500
#define BUZZER_DURATION_MS 100
#define REVERSE_DURATION_MS 2000

void left_wheel_set(direction_t dir);
void right_wheel_set(direction_t dir);
void set_TCB0(int state);
void set_TCB1(int state);
void set_TCB2(int state);
void set_TCD0(int state);
void set_gate(h_bridge_gate_t gate, int value);
void reverse_plus_buzzer(int ms);

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

void evade(int was_obstruction) {
    move(DIRECTION_NONE);
    
    reverse_plus_buzzer(REVERSE_DURATION_MS);
    
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
    move(DIRECTION_NONE);
    move(DIRECTION_FORWARD);
}

void move(direction_t dir) {
    left_wheel_set(dir);
    right_wheel_set(dir);
}

void reverse_plus_buzzer(int ms) {
    // Move
    move(DIRECTION_REVERSE);
    
    int i;
    for (i = 0; i < ms; i++) {
        if (i % BUZZER_INTERVAL_MS == 0) { // Play every BUZZER_INTERVAL_MS seconds
            set_buzzer(1);
            _delay_ms(BUZZER_DURATION_MS);
            set_buzzer(0);
            i += BUZZER_DURATION_MS; // Skip some iterations since BUZZER_DURATION_MS already passed
        }
        _delay_ms(1);
    }
    
    move(DIRECTION_NONE);
}


void left_wheel_set(direction_t dir) {
    switch (dir) {
        case DIRECTION_FORWARD:
            // Turn off reverse gates
            set_gate(LEFT_WHEEL_TOP_RIGHT, 0);
            set_gate(LEFT_WHEEL_BOTTOM_LEFT, 0);
            _delay_ms(500);
            // Turn on forward gates
            set_gate(LEFT_WHEEL_TOP_LEFT, 1);
            set_gate(LEFT_WHEEL_BOTTOM_RIGHT, 1);
            break;
        case DIRECTION_REVERSE:
            // Turn off forward gates
            set_gate(LEFT_WHEEL_TOP_LEFT, 0);
            set_gate(LEFT_WHEEL_BOTTOM_RIGHT, 0);
            _delay_ms(500);
            // Turn on reverse gates
            set_gate(LEFT_WHEEL_TOP_RIGHT, 1);
            set_gate(LEFT_WHEEL_BOTTOM_LEFT, 1);  
            break;
        case DIRECTION_NONE:
            // Turn off forward gates
            set_gate(LEFT_WHEEL_TOP_LEFT, 0);
            set_gate(LEFT_WHEEL_BOTTOM_RIGHT, 0);
            // Turn off reverse gates
            set_gate(LEFT_WHEEL_TOP_RIGHT, 0);
            set_gate(LEFT_WHEEL_BOTTOM_LEFT, 0);
            break;
    }
}

void right_wheel_set(direction_t dir) {
        switch (dir) {
            case DIRECTION_FORWARD:
                // Turn off reverse gates
                set_gate(RIGHT_WHEEL_TOP_RIGHT, 0);
                set_gate(RIGHT_WHEEL_BOTTOM_LEFT, 0);
                //_delay_ms(500);
                // Turn on forward gates
                set_gate(RIGHT_WHEEL_TOP_LEFT, 1);
                set_gate(RIGHT_WHEEL_BOTTOM_RIGHT, 1);
                break;
            case DIRECTION_REVERSE:
                // Turn off forward gates
                set_gate(RIGHT_WHEEL_TOP_LEFT, 0);
                set_gate(RIGHT_WHEEL_BOTTOM_RIGHT, 0);
                //_delay_ms(500);
                // Turn on reverse gates
                set_gate(RIGHT_WHEEL_TOP_RIGHT, 1);
                set_gate(RIGHT_WHEEL_BOTTOM_LEFT, 1);  
                break;
            case DIRECTION_NONE:
                // Turn off reverse gates
                set_gate(RIGHT_WHEEL_TOP_RIGHT, 0);
                set_gate(RIGHT_WHEEL_BOTTOM_LEFT, 0);
                // Turn off forward gates
                set_gate(RIGHT_WHEEL_TOP_LEFT, 0);
                set_gate(RIGHT_WHEEL_BOTTOM_RIGHT, 0);
                break;
        }
}

void rotate(spindirection_t dir, float radians){
    
}

void rotate_indefinite(spindirection_t dir) {
    switch (dir) {
        case Clockwise:
            left_wheel_set(DIRECTION_FORWARD);
            right_wheel_set(DIRECTION_REVERSE);
            break;
        case CounterClockwise:
            left_wheel_set(DIRECTION_REVERSE);
            right_wheel_set(DIRECTION_FORWARD);
            break;
    }
}

void TCB0_init_pwm(int perc_duty_cycle) {
    
    // Set output pins MUX
    PORTMUX.TCBROUTEA &= ~(1 << 0); // TCB0 PWM on PA2
    
    TCB0_set_duty_cycle(perc_duty_cycle);
    
    TCB0.CTRLA = (0 << 0); // Disable for now timer, use DIV1 for CLK 

    TCB0.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM modee

}

void TCB1_init_pwm(int perc_duty_cycle){
    // Set output pins MUX
    PORTMUX.TCBROUTEA &= ~(1 << 1); // TCB1 PWM on PA3
    
    TCB1_set_duty_cycle(perc_duty_cycle);

    TCB1.CTRLA = (0 << 0); // Disable for now timer, use DIV1 for CLK 

    TCB1.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
}

void TCB2_init_pwm(int perc_duty_cycle){
    // Set output pins MUX
    PORTMUX.TCBROUTEA &= ~(1 << 2); // TCB1 PWM on PA3
    
    TCB2_set_duty_cycle(perc_duty_cycle);
    
    TCB2.CTRLA = (0 << 0); // Disable for now timer, use DIV1 for CLK 

    TCB2.CTRLB = (1 << 4) | // Make output available on MUXed pin
                (0x7); // Use 8-bit PWM mode
}

void TCD0_init_pwm(int perc_duty_cycle){
    TCD0.CTRLB = 0x00; // Use one ramp mode

    TCD0_set_duty_cycle(perc_duty_cycle);
    
    _PROTECTED_WRITE(
            TCD0.FAULTCTRL, 
            (1 << 4) | // CMPA Enable
            (1 << 0) | // CMPA Value
            (1 << 5) | // CMPB Enable
            (1 << 1) // CMPB Value
        );
    
    // Wait for TCD to be ready
    while (!(TCD0.STATUS & (1 << 0))) {
        ;
    }
    
    // Set OSCHF as input clock
    TCD0.CTRLA &= ~((1 << 5) | (1 << 6));
    
    // We will enable inside set_TCD0 function
}

void set_TCB0(int state) {
    if (state) {
        TCB0.CTRLA |= (1 << 0); // Enable pwm waveform
    } else {
        TCB0.CTRLA &= ~(1 << 0); // Disable pwm waveform
    }
}

void set_TCB1(int state) {
    if (state) {
        TCB1.CTRLA |= (1 << 0); // Enable pwm waveform
    } else {
        TCB1.CTRLA &= ~(1 << 0); // Disable pwm waveform
    }
}

void set_TCB2(int state) {
    if (state) {
        TCB2.CTRLA |= (1 << 0); // Enable pwm waveform
    } else {
        TCB2.CTRLA &= ~(1 << 0); // Disable pwm waveform
    }
}


void set_TCD0(int state) {
    if (state) {
        TCD0.CTRLA |= (1 << 0); // Enable pwm waveform
    } else {
        TCD0.CTRLA &= ~(1 << 0); // Disable pwm waveform
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
            set_TCD0(value);
            break;
        case RIGHT_WHEEL_TOP_RIGHT:
            set_TCB2(value);
            break;
        case RIGHT_WHEEL_BOTTOM_LEFT:
            set_pin_output_value(R_REV_LO_D_OUT_PIN, D, value);
            break;
        case RIGHT_WHEEL_BOTTOM_RIGHT:
            set_pin_output_value(R_FOR_LO_D_OUT_PIN, D, value);
            break;
    }
}

void TCB0_set_duty_cycle(int perc_duty_cycle) {
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    TCB0.CCMPL = wave_per;
    TCB0.CCMPH = pulse_width;
}
void TCB1_set_duty_cycle(int perc_duty_cycle) {
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    TCB1.CCMPL = wave_per;
    TCB1.CCMPH = pulse_width;
}
void TCB2_set_duty_cycle(int perc_duty_cycle) {
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    TCB2.CCMPL = wave_per;
    TCB2.CCMPH = pulse_width;
}
void TCD0_set_duty_cycle(int perc_duty_cycle) {
    // Period
    uint8_t wave_per = F_CPU / (2 * PWM_FREQ) - 1;;
    uint8_t pulse_width = (uint8_t)((uint16_t)perc_duty_cycle * wave_per / 100);
    
    TCD0.CMPASET = 0x00;
    TCD0.CMPACLR = pulse_width;  
    
    TCD0.CMPBSET = 0x00;
    TCD0.CMPBCLR = wave_per;
}