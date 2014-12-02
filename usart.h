#ifndef ARDUINO_USART_H
#define ARDUINO_USART_H

#include <stdint.h>

// baudrate for UBRRn register, ATmega328P datasheet, p. 179
// UBRRn - [U]SART [B]aud [R]ate [R]egister
#define UBRR_VALUE(x) 	((F_CPU)/(x*16UL)-1)

#define USART_RECEIVE_STRING_ECHO	1

void usart_transmit_byte(unsigned char data);
void usart_transmit_string(const char *str);
uint8_t usart_receive_byte(void);
uint8_t usart_receive_string(char *buffer, uint8_t buffer_size);
void usart_init(uint16_t ubrr);

#endif
