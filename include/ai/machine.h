/**
 * @brief Declarations about the Ases machine.
 * @file machine.h
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#ifndef _MACHINE_H
#define _MACHINE_H

#include <stdio.h>
#include <inttypes.h>

/** The size of the data memory of a Ases machine */
#define AI_DATASIZE 65536

/** The list of valid instructions. */
#define AI_INSTRUCTIONS "abcdABCDpP$*()@!=><+-.?~0123456789"

/** The character for a comentary. */
#define AI_COMMENTARY '#'


#if __unix__
/** The format to print a register with color in Unix-Like system. */
#define AI_RPCOLOR "\x1b[31;1m%04" PRIx16 "\x1b[0m"
#else
/** Same as AI_RPRINT in system is not a Unix-Like. */
#define AI_RPCOLOR "%04" PRIx16
#endif /* __unix__ */

/** The format to print a register. */
#define AI_RPRINT "%04" PRIx16
typedef uint16_t ai_register_t;  /**< A register in te Ases machine. */

/**
 * @brief The status returned by ai_step() function
*/
typedef enum ai_step_status {
  STEP_OK = 0,
  STEP_EOF,
  STEP_NEXT_EOF,
  STEP_POINTER_INVALID,
  STEP_NOT_LMATCH,
  STEP_NOT_RMATCH,
  STEP_DP_OVERFLOW,
  STEP_DP_UNDERFLOW,
  STEP_FUNC_ERROR,
  STEP_FUNC_EXIT
} ai_step_status_t;

/**
 * @brief Linked list for stores the instructions.
*/
typedef struct ai_code {
  struct ai_code *right; /**< Pointer to the next struct. */
  struct ai_code *left;  /**< Pointer to the last struct. */
  int  index;            /**< Index of the instruction. */
  int  line;             /**< Line number in the source code. */
  int  column;           /**< Column number of the line in the source code. */
  char instruction;      /**< Instruction character. */
} ai_code_t;

/**
 * @brief Struct for stores the state of a Ases machine.
*/
typedef struct ai_machine {
  struct ai_code *code;             /**< Pointer to the code struct. */
  struct ai_code *first;            /**< Pointer to the first code struct. */
  ai_register_t data[AI_DATASIZE];  /**< Data memory. */
  ai_register_t stack;              /**< Stack register. */
  ai_register_t dp;                 /**< Data Pointer. */
  ai_register_t ra;                 /**< A register. */
  ai_register_t rb;                 /**< B register. */
  ai_register_t rc;                 /**< C register. */
  ai_register_t rd;                 /**< D register. */
} ai_machine_t;


ai_code_t        *ai_filter(FILE *input);
void              ai_code_error(ai_code_t *instruction, char *message);
ai_step_status_t  ai_step(ai_machine_t *machine);
ai_step_status_t  ai_run(ai_machine_t *machine);
void              ai_reset(ai_machine_t *machine);
ai_machine_t     *ai_machine_create(ai_code_t *code);
void              ai_console(ai_machine_t *machine);

#endif /* _MACHINE_H */
