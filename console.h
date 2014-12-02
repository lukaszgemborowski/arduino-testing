#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

typedef uint8_t (*io_read_string)(char*, uint8_t);
typedef void 	(*io_print_string)(const char*);

typedef struct console_driver
{
  io_read_string 	read_string;
  io_print_string 	print_string;
}
console_driver_t;

#endif
