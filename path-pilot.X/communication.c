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

void usart_init() {
    // Set PIND7 to output
    PORTD.DIRSET |= (1 << USART_D_OUT_PIN) | (1 << USART_D_IN_PIN);
    
    USART0.BAUD = (uint16_t)(9600);
    
    // Set the mode to synchronous and data format to 8-bit
    USART0.CTRLC = 0b10000011;
    
    // Enable transmission
    USART0.CTRLB |= (1 << 6);                      
}

void usart_send_str(char *str) {
    for(size_t i = 0; i < strlen(str); i++)    
    {        
        usart_send_char(str[i]);    
    }
}

void usart_send_char(char c) {
    // Wait until the register is ready for new data (pg. 377 of DS)
    while(!(USART0.STATUS & (1 << 5)))
    {
        ;
    }
    
    USART0.TXDATAL = c;
    
    // For testing
    //while (1) {
    //    // Transmit complete
    //    if (USART0.STATUS & (1 << 6)) {
    //        char a[] = "test";
    //        usart_send_str(&a);
    //    }
    //}
    
}
