#include <avr/io.h>
#include <util/delay.h>

int main()
{
  // pin mapping can be found @ http://arduino.cc/en/Hacking/PinMapping168
  DDRB |= (1 << 5);
  
  for (;;)
  {
    // blink LED
    PORTB ^= (1 << 5);
    _delay_ms(1500.0);
  }
}
