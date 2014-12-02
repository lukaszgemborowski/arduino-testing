#include <stdio.h>
#include "shell.h"

void usart_transmit_string(const char *str)
{
  puts(str);
}

uint8_t usart_receive_string(char *buffer, uint8_t buffer_size)
{
  gets(buffer);
}

int main()
{
   console_driver_t console = {
    &usart_receive_string, //read_string
    &usart_transmit_string // print_string
  };

  start_shell(&console);
}
