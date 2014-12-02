#include "shell.h"
#include "usart.h"

#include <string.h>

// input buffer length
#define MAX_INPUT_LENGTH 255

// input buffer
static char g_input_buffer[MAX_INPUT_LENGTH];

// prompt string
static const char* g_prompt = "$ ";

// I/O driver pointer
static console_driver_t* g_console = 0;

// shell state information
typedef struct shell_state_t
{
  char running;
} shell_state;

typedef enum 
{
  EBuiltInCommand_Ping,
  EBuiltInCommand_Help,
  EBuiltInCommand_None
} EBuiltInCommand;

// check if given string starts from specified command
uint8_t is_command(const char* command, const char* input, uint8_t command_length)
{
  return (strncmp(input, command, command_length) == 0) && 
    (input[command_length] == ' ' || input[command_length] == '\0');
}

EBuiltInCommand check_command(const char *input)
{
  // check commands. It is guaranteed that "input" 
  // is at least MAX_INPUT_LENGTH
  // so we only need remember that command strings
  // should be shorter than MAX_INPUT_LENGTH
  if (is_command("ping", input , 4))
  {
    return EBuiltInCommand_Ping;
  }
  else if (is_command("help", input, 4))
  {
    return EBuiltInCommand_Help;
  }
  
  return EBuiltInCommand_None;
}

void process_input(shell_state* shell, const char *input)
{
  switch(check_command(input))
  {
    case EBuiltInCommand_Ping:
      g_console->print_string("PONG!\r\n");
      break;
      
    case EBuiltInCommand_Help:
      g_console->print_string("Available commands are:\r\n\tping - to get response from board\r\n\thelp - display this message\r\n");
      break;
      
    case EBuiltInCommand_None:
      g_console->print_string("Command not found\r\n");
      break;
  }
}

void start_shell(console_driver_t *console)
{
  g_console = console;
  shell_state state = { 1 };
  
  do
  {
    g_console->print_string(g_prompt);
    g_console->read_string(g_input_buffer, MAX_INPUT_LENGTH);
    
    process_input(&state, g_input_buffer);
  }
  while(state.running != 0);
}
