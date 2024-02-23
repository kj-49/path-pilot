/* 
 * File:   communication.h
 * Author: Kyle James
 *
 * Created on February 4, 2024, 4:34 PM
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

void usart_init();
void usart_send_str(const char *str);
void usart_send_char(char c);

void u_println(const char *str);


#endif	/* COMMUNICATION_H */

