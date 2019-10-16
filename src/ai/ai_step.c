/**
 * @brief ai_step() source code.
 * @file ai_step.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include "ai/machine.h"

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
static void ai_code_error(ai_code_t *instruction, char *message)
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
 * @retval  0          If all OK.
 * @retval  non-zero   If a error occurs.
*/
int ai_step(ai_machine_t *machine)
{
  ai_code_t *instruction;

  if (!machine || !machine->code)
    return 1;
  
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
      machine->rd = machine->code->index;
      break;
    case '*':
      instruction = ai_code_sindex(machine->first, machine->rd);
      if (!instruction) {
        ai_code_error(machine->code, "Pointer in D register is not valid.");
        return 2;
      }

      machine->code = instruction;
      goto end_code;
    case ')':
      instruction = ai_code_smatch(machine->code, 'L');
      if (!instruction) {
        ai_code_error(machine->code, "Not matched `@' in the left.");
        return 3;
      }

      machine->code = instruction;
      goto end_code;
    case '(':
      instruction = ai_code_smatch(machine->code, 'R');
      if (!instruction) {
        ai_code_error(machine->code, "Not matched `@' in the right.");
        return 3;
      }

      machine->code = instruction;
      goto end_code;
    case '!':
      machine->data[ machine->dp ] = machine->stack;
      break;
    case '=':
      machine->stack = machine->data[ machine->dp ];
      break;
    case '>':
      if (machine->dp + 1 < machine->dp) {
        ai_code_error(machine->code, "Data pointer's overflow.");
        return 4;
      }

      machine->dp++;
      break;
    case '<':
      if (machine->dp - 1 > machine->dp) {
        ai_code_error(machine->code, "Data pointer's underflow.");
        return 5;
      }

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
  }

  machine->code = machine->code->right;

end_code:
  return 0;
}