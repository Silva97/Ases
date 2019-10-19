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
    case STEP_BREAK:           message = "Breakpoint";            break;
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
  ai_code_t *code;
  int  address;
  int  line;
  int  column;
  int  count;
  int  step;
  char input[64];

  while (true) {
    puts("\n_____________________");
    if (machine->code) {
      ai_context(machine, 10);
      address = machine->code->index;
      line    = machine->code->line;
      column  = machine->code->column;
    } else {
      address = 0;
      line    = 0;
      column  = 0;
    }

    ai_state(machine);
    printf("<line,column> %d,%d  "
           "<address> " AI_RPRINT "  "
           "<status> %s\n- ",
           line,
           column,
           address,
           ai_get_status(status));

    while ( !fgets(input, sizeof input - 1, stdin) && input[0] == '\n' );

    switch (input[0]) {
      case 'b':
        address = 0;
        sscanf(&input[1], "%i", &address);
        if (!address) {
          fputs("Error: Invalid address value\n", stderr);
        } else {
          code = ai_code_sindex(machine->first, address);
          code->breakpoint = true;
          printf("* Defined breakpoint at instruction `%c'\n",
                 code->instruction);
        }
        break;
      case 'u':
        address = 0;
        sscanf(&input[1], "%i", &address);
        if (!address) {
          fputs("Error: Invalid address value\n", stderr);
        } else {
          code = ai_code_sindex(machine->first, address);
          code->breakpoint = false;
        }
        break;
      case 'l':
        code = machine->first;

        while (code) {
          if (code->breakpoint) {
            printf(AI_RPRINT ": %c\n", code->index, code->instruction);
          }
          code = code->right;
        }

        break;
      case 'r':
        ai_reset(machine);
        break;
      case 's':
        step = 1;
        sscanf(&input[1], "%i", &step);
        
        for (; step; step--)
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
        address = 0;
        count   = 0;
        sscanf(&input[1], "%i %i", &address, &count);
        
        if (!count) {
          fputs("Error: Invalid <a> or <c> value.\n", stderr);
        } else {
          ai_dump(machine, (ai_register_t) address, (ai_register_t) count);
        }
        
        break;
      case 'q':
        return;
      case '?':
        puts(
          "Commands:\n"
          "  r          Reset the script.\n"
          "  c          Continuous run the script.\n"
          "  s [n]      Run N steps of the script. Default 1.\n"
          "  b <a>      Define a breakpoint in A address.\n"
          "  u <a>      Undefine a breakpoint in A address.\n"
          "  l          List all breakpoints.\n"
          "  n          Go to next instruction without run it.\n"
          "  p          Go to previous instruction without run it.\n"
          "  d <a> <c>  Dumps C counts of data's memory from A address.\n"
          "  q          Quit.\n\n"
          
          "Any value can be in decimal, hexadecimal or octal. Following the format:\n"
          "  0x2a   Hexadecimal\n"
          "  42     Decimal\n"
          "  052    Octal"
        );
        break;
      case '\n':
        break;
      default:
        fprintf(stderr, "Unknown '%c' command.\n", input[0]);
    }
  }
}
