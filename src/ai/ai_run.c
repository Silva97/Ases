/**
 * @brief The ai_run() and ai_reset() source code.
 * @file ai_run.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include <string.h>
#include "ai/ai.h"

/**
 * @brief Run the Ases machine while status is 'STEP_OK'.
 * @param   machine    The Asus machine to run.
*/
ai_step_status_t ai_run(ai_machine_t *machine)
{
  ai_step_status_t status;

  while ( (status = ai_step(machine)) == STEP_OK );

  return status;
}

/**
 * @brief Reset the Ases machine.
 * @param   machine    The Ases machine.
*/
void ai_reset(ai_machine_t *machine)
{
  memset(machine->data, 0, AI_DATASIZE * sizeof (ai_register_t));

  machine->code  = machine->first;
  machine->dp    = 0;
  machine->stack = 0;
  machine->ra    = 0;
  machine->rb    = 0;
  machine->rc    = 0;
  machine->rd    = 0;
}