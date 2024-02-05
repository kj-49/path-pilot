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
    PORTD.DIRSET |= (1 << USART_D_OUT_PIN);
    
    USART1.BAUD = (uint16_t)(9600);
    
    // Set the data format to 8-bit
    USART1.CTRLC = 0b00000011;
    
    // Enable transmission
    USART1.CTRLB |= (1 << 6);                      
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
    
    USART1.TXDATAL = c;
}
