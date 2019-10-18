/**
 * @brief The ai_console() source code.
 * @file ai_console.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include <stdio.h>
#include <stdbool.h>
#include "ai/ai.h"

/**
 * @brief Gets the status message.
 * @return The text message about the status.
*/
static char *ai_get_status(ai_step_status_t status)
{
  char *message;

  switch (status) {
    case STEP_OK:              message = "OK";                    break;
    case STEP_EOF:             message = "EOF";                   break;
    case STEP_NEXT_EOF:        message = "Error next EOF";        break;
    case STEP_POINTER_INVALID: message = "Error pointer invalid"; break;
    case STEP_NOT_LMATCH:      message = "Error not L-match";     break;
    case STEP_NOT_RMATCH:      message = "Error not R-match";     break;
    case STEP_DP_OVERFLOW:     message = "Error DP Overflow";     break;
    case STEP_DP_UNDERFLOW:    message = "Error DP Underflow";    break;
    case STEP_FUNC_ERROR:      message = "Function 2 error exit"; break;
    case STEP_FUNC_EXIT:       message = "Function 3 exit";       break;
    default:                   message = "Unknown";               break;
  }

  return message;
}

/**
 * @brief Run the machine in a console debugger.
 * @param   machine    The Ases machine.
*/
void ai_console(ai_machine_t *machine)
{
  ai_step_status_t status = STEP_OK;
  int  start;
  int  count;
  char input[64];

  while (true) {
    puts("\n----------");
    if (machine->code)
      ai_context(machine, 10);
    
    ai_state(machine);
    printf("<status> %s\n- ", ai_get_status(status));

    while ( !fgets(input, sizeof input - 1, stdin) && input[0] == '\n' );

    switch (input[0]) {
      case 'r':
        ai_reset(machine);
        break;
      case 's':
        status = ai_step(machine);
        break;
      case 'c':
        status = ai_run(machine);
        break;
      case 'n':
        if (!machine->code || !machine->code->right) {
          fputs("Error: No have next instruction (EOF)\n", stderr);
        } else {
          machine->code = machine->code->right;
        }

        break;
      case 'p':
        if (!machine->code || !machine->code->left) {
          fputs("Error: No have previous instruction\n", stderr);
        } else {
          machine->code = machine->code->left;
        }

        break;
      case 'd':
        start = 0;
        count = 0;
        sscanf(&input[1], "%i %i", &start, &count);
        
        if (!count) {
          fputs("Error: Invalid <a> or <c> value.\n", stderr);
        } else {
          ai_dump(machine, start, count);
        }
        
        break;
      case 'q':
        return;
      case '?':
        puts(
          "Commands:\n"
          "  r          Reset the script.\n"
          "  c          Continuous run the script.\n"
          "  s          Run one step of the script.\n"
          "  n          Go to next instruction without run it.\n"
          "  p          Go to previous instruction without run it.\n"
          "  d <a> <c>  Dumps <c> counts of data's memory from <a> address.\n"
          "  q          Quit."
        );
        break;
      case '\n':
        break;
      default:
        fprintf(stderr, "Unknown '%c' command.\n", input[0]);
    }
  }
}
