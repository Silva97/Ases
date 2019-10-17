/*
 * Developed by Luiz Felipe.
 * This is the source code of the Ases interpreter,
 * distributed under the MIT License.
 * 
 * GitHub: https://github.com/Silva97/Ases
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "ai/ai.h"

void show_help();

int main(int argc, char **argv)
{
  FILE         *input;
  ai_code_t    *code;
  ai_machine_t *ases;
  char          opt;
  bool          debug = false;

  while ( (opt = getopt(argc, argv, "c:dh")) > 0 ) {
    switch (opt) {
      case 'c':
        if ( !strcmp(optarg, "-") ) {
          input = stdin;
        } else {
          input = fopen(optarg, "r");
          if (!input) {
            fprintf(stderr, "File '%s' not found.\n", optarg);
            exit(EXIT_FAILURE);
          }
        }

        code = ai_filter(input);
        while (code) {
          putchar(code->instruction);
          code = code->right;
        }

        putchar('\n');
        exit(EXIT_SUCCESS);
      case 'd':
        debug = true;
        break;
      case 'h':
        show_help();
        exit(EXIT_SUCCESS);
      default:
        fprintf(stderr, "See help: %s -h\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc || !strcmp(argv[optind], "-")) {
    input = stdin;
  } else {
    input = fopen(argv[optind], "r");
    if (!input) {
      fprintf(stderr, "File '%s' not found.\n", argv[optind]);
      exit(EXIT_FAILURE);
    }
  }

  ases = ai_machine_create( ai_filter(input) );

  if (debug) {
    puts("* Run '?' to see help.");
    ai_console(ases);
    exit(EXIT_SUCCESS);
  }

  switch ( ai_run(ases) ) {
    case STEP_NEXT_EOF:
      ai_code_error(ases->code, "This instruction can't be used in EOF.");
      exit(EXIT_FAILURE);
    case STEP_POINTER_INVALID:
        ai_code_error(ases->code, "Pointer in D register is not valid.");
        exit(EXIT_FAILURE);
    case STEP_NOT_LMATCH:
      ai_code_error(ases->code, "Not matched `@' in the left.");
      exit(EXIT_FAILURE);
    case STEP_NOT_RMATCH:
      ai_code_error(ases->code, "Not matched `@' in the right.");
      exit(EXIT_FAILURE);
    case STEP_DP_OVERFLOW:
      ai_code_error(ases->code, "Data pointer's overflow.");
      exit(EXIT_FAILURE);
    case STEP_DP_UNDERFLOW:
      ai_code_error(ases->code, "Data pointer's underflow.");
      exit(EXIT_FAILURE);
    case STEP_FUNC_ERROR:
      fputs("ERROR!\n", stderr);
      exit(255);
    case STEP_FUNC_EXIT:
      exit( ases->stack );
    default:
      /* Do nothing */
      break;
  }

  return 0;
}

/**
 * @brief Shows the help message.
*/
void show_help()
{
  puts(
    "Ases - Interpreter to Ases esoteric programming language.\n"
    "Developed by Luiz Felipe <felipe.silva337@yahoo.com>\n"
    "GitHub: https://github.com/Silva97/Ases\n\n"

    "Usage: ases [-c,-d] [file]\n"
    "  -c  <filename>    Compact the ases code and print it.\n"
    "  -d                Run the code in debug mode.\n"
    "  file              The Ases script. If not defined, read from stdin.\n\n"

    "ASES INSTRUCTIONS\n"
    "  a,b,c,d    Stores the value of the stack in correspondent register.\n"
    "  A,B,C,D    Gets the value of the register and stores in the stack.\n"
    "  p          Stores the value of the stack in the Data Pointer.\n"
    "  P          Gets the value of Data Pointer and stores in the stack.\n"
    "  $          Stores the address of the next instruction in D register.\n"
    "  *          Jumps for the instruction pointed by D register.\n"
    "  (          Jumps for the instruction `@' matched in the right.\n"
    "  )          Jumps for the instruction `@' matched in the left.\n"
    "  @          Does nothing.\n"
    "  !          Stores the value of the stack in memory pointed by DP.\n"
    "  =          Gets the value of memory pointed by DP and store in stack.\n"
    "  >          Increments the value of Data Pointer (DP).\n"
    "  <          Decrements the value of Data Pointer (DP).\n"
    "  +          Increments the value of the stack.\n"
    "  -          Decrements the value of the stack.\n"
    "  .          Set value of the stack to zero.\n"
    "  ?          Only executes the next instruction if `stack == 0`.\n"
    "  ~          Only executes the next instruction if `stack != 0`.\n"
    "  #          Commentary of one line.\n\n"

    "ASES FUNCTIONS\n"
    "  0          Gets input of one character and stores in the stack.\n"
    "  1          Output the character in the stack.\n"
    "  2          Prints 'ERROR!' and stop the program. (status = 255)\n"
    "  3          Exits the program. (status = stack)\n"
    "  4          A += stack\n"
    "  5          A -= stack\n"
    "  6          stack += 10\n"
    "  7          stack -= 10\n"
    "  8          Prints the state of the machine.\n"
    "  9          If A > B, sets the stack to 1. Sets to 0 otherwise."
  );
}