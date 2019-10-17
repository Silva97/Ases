/**
 * @brief The ai_context() source code.
 * @file ai_context.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include "ai/ai.h"

/**
 * @brief Prints the code context.
 * @param   machine    The Ases machine to print the context.
 * @param   size       The context's size.
 * 
 * The 'size' instructions left and right is printed in stdout.
 * The current instruction is pointed with '^' character.
*/
void ai_context(ai_machine_t *machine, int size)
{
  int       n     = 0;
  int       index = machine->code->index;
  ai_code_t *code = machine->code;

  for (int i = 0; i < size; i++) {
    if (!code->left)
      break;
    code = code->left;
  }

  for (int i = 0; i < size*2 + 1; i++) {
    putchar(code->instruction);

    if (code->index <= index)
      n++;

    if (!code->right)
      break;

    code = code->right;
  }

  printf("\n%*c\n", n, '^');
}