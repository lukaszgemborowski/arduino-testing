#include "usart.h"
#include "shell.h"

int main()
{
  // initialize USART driver
  usart_init(UBRR_VALUE(9600));
  usart_transmit_string("Arduino 0.1 initializing.\r\n");
  
  console_driver_t console = {
    &usart_receive_string, //read_string
    &usart_transmit_string // print_string
  };

  start_shell(&console);
  
  return 0;
}
