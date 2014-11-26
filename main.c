#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

int main()
{
  // pin mapping can be found @ http://arduino.cc/en/Hacking/PinMapping168
  DDRB |= (1 << 5);

  _delay_ms(500.0);

  // init usart controller
  usart_init(UBRR_VALUE(9600));

  // send string to receiver
  usart_transmit_string("Hello world!\r\n");

  for (;;)
  {
    // blink LED
    PORTB ^= (1 << 5);
    _delay_ms(1500.0);
  }
}
