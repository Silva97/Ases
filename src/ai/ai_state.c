/**
 * @brief The ai_state() source code.
 * @file ai_state.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include "ai/ai.h"

/**
 * @brief Prints te state of the machine.
 * @param   machine    The Ases machine to print.
 *
 * Show the value of all the registers in hexadecimal.
 */
void ai_state(ai_machine_t *machine)
{
  printf("Stack = " AI_RPRINT
         " | A = " AI_RPRINT
         " | B = " AI_RPRINT
         " | C = " AI_RPRINT
         " | D = " AI_RPRINT
         " | E = " AI_RPRINT
         " | F = " AI_RPRINT "\n"
         "   DP = " AI_RPRINT
         " | G = " AI_RPRINT
         " | H = " AI_RPRINT
         " | I = " AI_RPRINT
         " | J = " AI_RPRINT
         " | K = " AI_RPRINT
         " | L = " AI_RPRINT "\n",
         machine->stack,
         machine->ra,
         machine->rb,
         machine->rc,
         machine->rd,
         machine->re,
         machine->rf,
         machine->dp,
         machine->rg,
         machine->rh,
         machine->ri,
         machine->rj,
         machine->rk,
         machine->rl);
}