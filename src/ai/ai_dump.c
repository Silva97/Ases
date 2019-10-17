/**
 * @brief The ai_dump() source code.
 * @file ai_dump.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include "ai/ai.h"

/**
 * @brief Dumps the data memory of a Ases machine.
 * @param   machine    The Ases machine.
 * @param   start      The initial index to dump.
 * @param   count      The number of elements to dump.
*/
void ai_dump(ai_machine_t *machine, unsigned int start, unsigned int count)
{
  unsigned int i;

  if (start+count > AI_DATASIZE) {
    count = count - ( (start+count) % AI_DATASIZE );
  }

  for (i = 0; i < count; i++) {
    if ( !(i%8) ) {
      printf(AI_RPRINT ": ", start + i);
    }
    
    if (start + i == machine->dp) {
      printf(AI_RPCOLOR  " ", machine->data[start + i]);
    } else {
      printf(AI_RPRINT  " ", machine->data[start + i]);
    }

    if (i%8 == 7) {
      putchar('\n');
    }
  }

  if (i%8) {
    putchar('\n');
  }
}