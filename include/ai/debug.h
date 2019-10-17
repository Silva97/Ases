/**
 * @brief Declarations about the Ases debugger.
 * @file debug.h
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#ifndef _DEBUG_H
#define _DEBUG_H

#include "ai/machine.h"

void ai_state(ai_machine_t *machine);
void ai_context(ai_machine_t *machine, int size);
void ai_dump(ai_machine_t *machine, unsigned int start, unsigned int count);

#endif /* _DEBUG_H */