#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

int main()
{
  // pin mapping can be found:
  // http://arduino.cc/en/Hacking/PinMapping168
  // in this case we'll set pin13 as output
  // This call is equivalent to pinMode(13, OUTPUT)
  DDRB |= (1 << 5);

  // init usart controller (see usart.c)
  usart_init(UBRR_VALUE(9600));

  // send string to receiver
  usart_transmit_string("Hello world!\r\nType something: ");
  
  // receive max 10 bytes
  char buffer[10];
  usart_receive_string(buffer, 10);
  
  // transmit buffer back to client
  usart_transmit_string("\r\nReceived string: ");
  usart_transmit_string(buffer);

  for (;;)
  {
    // toggle bit in PORTB, this should turn off and on
    // LED connected to pin13. This is the same as call
    // to digitalWrite(13, LOW) or HIGH
    PORTB ^= (1 << 5);

    // wait 1.5 sec
    _delay_ms(1500.0);
  }
}
