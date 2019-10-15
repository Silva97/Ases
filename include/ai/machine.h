/**
 * @brief Declarations about the Ases machine.
 * @file machine.h
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#ifndef _MACHINE_H
#define _MACHINE_H

#include <inttypes.h>

/** The list of valid instructions. */
#define AI_INSTRUCTIONS "abcdABCDpP$*()@!><+-.?~"

/** The character for a comentary. */
#define AI_COMMENTARY '#'

typedef uint16_t ai_register_t;  /**< A register in te Ases machine. */

/**
 * @brief Linked list for stores the instructions.
*/
typedef struct ai_code {
  struct ai_code *next; /**< Pointer to the next struct. */
  struct ai_code *last; /**< Pointer to the last struct. */
  int  line;            /**< Line number in the source code. */
  int  column;          /**< Column number of the line in the source code. */
  char instruction;     /**< Instruction character. */
} ai_code_t;

/**
 * @brief Struct for stores the state of a Ases machine.
*/
typedef struct ai_machine {
  struct ai_code *code;      /**< Pointer to the code struct. */
  ai_register_t data[65536]; /**< Data memory. */
  ai_register_t stack;       /**< Stack register. */
  ai_register_t dp;          /**< Data Pointer. */
  ai_register_t ra;          /**< A register. */
  ai_register_t rb;          /**< B register. */
  ai_register_t rc;          /**< C register. */
  ai_register_t rd;          /**< D register. */
} ai_machine_t;


/** Filter the invalid characters. */
ai_code_t *ai_filter(FILE *input);

/** Run one step in the Ases machine. */
int ai_step(ai_machine_t *machine);

#endif /* _MACHINE_H */