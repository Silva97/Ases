/**
 * @brief ai_filter() source code.
 * @file ai_filter.c
 * @author Luiz Felipe <felipe.silva337@yahoo.com>
 * @date 10/2019
 * @copyright MIT License
*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ai/machine.h"

/**
 * @brief   Filter the code and return the code.
 * @param   input    The file for read the instructions
 * @return  The linked list to the code
 *
 * Reads the instructions filtering all non-valid characters and removing
 * the commentaries. Stops in the End Of File.
 * The AI_INSTRUCTIONS macro is the list of valids characters.
 * AI_COMMENTARY is the character to one-line commentaries.
*/
ai_code_t *ai_filter(FILE *input)
{
  int c;
  int line         = 1;
  int column       = 1;
  int index        = 0;
  bool commentary  = false;
  ai_code_t *last  = NULL;
  ai_code_t *first = NULL;
  ai_code_t *next;

  while ((c = fgetc(input)) != EOF) {
    switch (c) {
      case '\r':
        c = fgetc(input);
        if (c != '\n') ungetc(c, input);
      case '\n':
        line++;
        column     = 1;
        commentary = false;
        continue;

      case AI_COMMENTARY:
        commentary = true;
        continue;

      default:
        if (commentary) continue;
    }

    if (strchr(AI_INSTRUCTIONS, c)) {
      next              = malloc( sizeof (ai_code_t) );
      next->index       = index++;
      next->line        = line;
      next->column      = column++;
      next->instruction = c;
      next->right       = NULL;

      if (!last) {
        next->left = NULL;
        last       = next;
        first      = last;
      } else {
        last->right = next;
        next->left  = last;
        last        = next;
      }
    }
  }

  return first;
}