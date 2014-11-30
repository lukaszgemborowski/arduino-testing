#include "usart.h"
#include <avr/io.h>

void usart_init(unsigned short ubrr)
{
  // set baudrate in UBR register
  UBRR0H = ubrr>>8;
  UBRR0L = ubrr;

  // enable TX & RX
  UCSR0B |= (1<<TXEN0)|(1<<RXEN0);

  // [U]SART [S]top [B]it [S]elect:
  // 0 - 1 bit stop
  // 1 - 2 bit stop

  // [U]SART [C]haracter [S]i[Z]e:
  // 000b - 5-bit
  // 001b - 6-bit
  // 010b - 7-bit
  // 011b - 8-bit
  // 111b - 9-bit
  UCSR0C |= (1<<USBS0)|(3<<UCSZ00);
}

unsigned char usart_receive_byte(void)
{
  while (!(UCSR0A & (1<<RXC0)))
    ;
  
  return UDR0;
}

unsigned char usart_receive_string(char *buffer, unsigned short buffer_size)
{
  unsigned short pos = 0;
  unsigned char data = 0;
  
  while(pos < buffer_size-1)
  {
    data = usart_receive_byte();
    
    if (data == '\r')
    {
      // end of string
      break;
    }
    else
    {
#ifdef USART_RECEIVE_STRING_ECHO
      // send back byte (echo)
      usart_transmit_byte(data);
#endif
      
      // normal byte, add to buffer and
      // increment position pointer
      buffer[pos] = data;
      pos ++;
    }
  }

  // set null terminator
  buffer[pos] = 0;

  return pos;
}

void usart_transmit_byte(unsigned char data)
{
  // UDRE - [U]SART [D]ata [R]egister [E]mpty
  while(!(UCSR0A & (1<<UDRE0)))
    ;
 
  UDR0 = data;
}

void usart_transmit_string(const char *str)
{
  while (*str)
  {
    usart_transmit_byte(*str++);
  }
}
