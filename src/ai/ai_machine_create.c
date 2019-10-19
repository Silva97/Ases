/**
 * @brief The ai_machine_create() source code.
 * @file ai_machine_create.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include <stdlib.h>
#include "ai/machine.h"

/**
 * @brief Creates a new Ases machine.
 * @param   code    The code struct to the machine.
 * @return  The pointer to the new machine.
 * 
 * All the values is initialized with zero.
 * The m->code and m->first is defined to the 'code' argument.
*/
ai_machine_t *ai_machine_create(ai_code_t *code)
{
  ai_machine_t *machine = calloc(1, sizeof (ai_machine_t));
  machine->code         = code;
  machine->first        = code;

  return machine;
}