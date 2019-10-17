/**
 * @brief The ai_step() and ai_code_error() source code.
 * @file ai_step.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include <stdlib.h>
#include "ai/ai.h"

/**
 * @brief   Search for a instruction by the index.
 * @param   code     The code struct.
 * @param   index    The index of the instruction to search.
 * @retval  NULL     If not find the instruction.
 * @return  The pointer to the instruction.
*/
static ai_code_t *ai_code_sindex(ai_code_t *code, int index)
{
  while (code && code->index != index) {
    if (code->index > index) {
      code = code->left;
    } else {
      code = code->right;
    }
  }

  return code;
}

/**
 * @brief Search for matched '@' for left or right.
 * @param   code       The initial instruction.
 * @param   direction  'L' to left, 'R' to right.
 * @retval  NULL       If not matched any instruction.
 * @return  The matched instruction.
*/
static ai_code_t *ai_code_smatch(ai_code_t *code, char direction)
{
  char instruction = (direction == 'L')? ')' : '(';
  int  context     = 1;

  if (!code) return NULL;

  while (context > 0) {
    if (direction == 'L') {
      code = code->left;
    } else {
      code = code->right;
    }

    if (!code) break;

    if (code->instruction == instruction) {
      context++;
    } else if (code->instruction == '@') {
      context--;
    }
  }

  return code;
}

/**
 * @brief Prints a error message with informations about the instruction.
 * @param    instruction    The failed instruction.
 * @param    message        The error message to print.
*/
void ai_code_error(ai_code_t *instruction, char *message)
{
  fprintf(stderr, "[%d:%d] Instruction `%c' error:\n  %s\n",
          instruction->line,
          instruction->column,
          instruction->instruction,
          message);
}

/**
 * @brief   Run one step of the Ases machine.
 * @param   machine    The Ases machine to run the instruction.
 * @return  The status of the machine.
*/
ai_step_status_t ai_step(ai_machine_t *machine)
{
  ai_code_t *instruction;
  ai_step_status_t status = STEP_OK;

  if (!machine || !machine->code)
    return STEP_EOF;
  
  switch (machine->code->instruction) {
    case '@':
      /* Do nothing */
      break;
    case 'a':
      machine->ra = machine->stack;
      break;
    case 'b':
      machine->rb = machine->stack;
      break;
    case 'c':
      machine->rc = machine->stack;
      break;
    case 'd':
      machine->rd = machine->stack;
      break;
    case 'p':
      machine->dp = machine->stack;
      break;
    case 'A':
      machine->stack = machine->ra;
      break;
    case 'B':
      machine->stack = machine->rb;
      break;
    case 'C':
      machine->stack = machine->rc;
      break;
    case 'D':
      machine->stack = machine->rd;
      break;
    case 'P':
      machine->stack = machine->dp;
      break;
    case '$':
      if (!machine->code->right)
        return STEP_NEXT_EOF;

      machine->rd = machine->code->right->index;
      break;
    case '*':
      instruction = ai_code_sindex(machine->first, machine->rd);
      if (!instruction)
        return STEP_POINTER_INVALID;

      machine->code = instruction;
      goto end_code;
    case ')':
      instruction = ai_code_smatch(machine->code, 'L');
      if (!instruction)
        return STEP_NOT_LMATCH;

      machine->code = instruction;
      goto end_code;
    case '(':
      instruction = ai_code_smatch(machine->code, 'R');
      if (!instruction)
        return STEP_NOT_RMATCH;

      machine->code = instruction;
      goto end_code;
    case '!':
      machine->data[ machine->dp ] = machine->stack;
      break;
    case '=':
      machine->stack = machine->data[ machine->dp ];
      break;
    case '>':
      if (machine->dp + 1 > (ai_register_t) -1)
        return STEP_DP_OVERFLOW;

      machine->dp++;
      break;
    case '<':
      if (machine->dp - 1 < 0)
        return STEP_DP_UNDERFLOW;

      machine->dp--;
      break;
    case '+':
      machine->stack++;
      break;
    case '-':
      machine->stack--;
      break;
    case '.':
      machine->stack = 0;
      break;
    case '?':
      if (machine->stack && machine->code->right) {
        machine->code = machine->code->right;
      }
      break;
    case '~':
      if (!machine->stack && machine->code->right) {
        machine->code = machine->code->right;
      }
      break;
    case '0':
      machine->stack = getchar();
      break;
    case '1':
      putchar(machine->stack);
      break;
    case '2':
      status = STEP_FUNC_ERROR;
      break;
    case '3':
      status = STEP_FUNC_EXIT;
      break;
    case '4':
      machine->ra += machine->stack;
      break;
    case '5':
      machine->ra -= machine->stack;
      break;
    case '6':
      machine->stack += 10;
      break;
    case '7':
      machine->stack -= 10;
      break;
    case '8':
      ai_state(machine);
      break;
    case '9':
      machine->stack = (machine->ra <= machine->rb);
      break;
  }

  machine->code = machine->code->right;

end_code:
  return status;
}