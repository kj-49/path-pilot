/* 
 * File:   communication.c
 * Author: Kyle James
 *
 * Created on February 4, 2024, 4:28 PM
 */

#include <avr/io.h>
#include <string.h>

#include "communication.h"
#include "avr-common.h"


#define BAUD_RATE_CALC(BAUD_RATE) ((float)(64 * 1000000 / (16 * (float)BAUD_RATE)) + 0.5)


void usart_init() {
    // Set PIND7 to output
    PORTD.DIRSET |= (1 << USART_D_OUT_PIN) | (1 << USART_D_IN_PIN);
    
    //USART1.BAUD = (uint16_t)(BAUD_RATE_CALC(9600));
    
    // Set the mode to synchronous and data format to 8-bit
    USART1.CTRLC = 0b10000011;
    
    // Enable transmission and auto baud.
    USART1.CTRLB |= (1 << 6) | (1 << 7) | (1 << 3);                      
}

void usart_send_str(char *str) {
    for(size_t i = 0; i < strlen(str); i++)    
    {        
        usart_send_char(str[i]);    
    }
}

void usart_send_char(char c) {
    // Wait until the register is ready for new data (pg. 377 of DS)
    while(!(USART1.STATUS & (1 << 5)))
    {
        ;
    }
    
    USART0.TXDATAH = c;
    
    while (!(USART1.STATUS & (1 << 6)));
    
    while (!(USART1.STATUS & (1 << 6)));
    // For testing
    //while (1) {
    //    // Transmit complete
    //    if (USART0.STATUS & (1 << 6)) {
    //        char a[] = "test";
    //        usart_send_str(&a);
    //    }
    //}
    
}
