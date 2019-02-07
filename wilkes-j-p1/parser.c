/* This file iterates through the token linked list and checks if the order of tokens/types is valid based on the rules set forth in the project. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/07/2019
*/

#include "parser.h"
#include "linkedList.h"
#include "errorList.h"
#include <string.h>
#include <stdbool.h>

struct lexemeNode
{
  int line;
  char word[30];
  char whatAmI[15];
  lexemeNode *next;
};

#define RESWORD "reserved word"
#define OPERATOR "operator"
#define DELIMITER "delimiter"
#define IDENTIFIER "identifier"
#define VALUE "value"

/* Returns result of parsing through program. */
bool isValidProgram()
{
  lexemeNode *runner = getHead();
  if (strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "begin") != 0)
  {
    if (getErrorHead() == NULL)
    {
      createErrorList(runner->line, "ERROR: Program must start with 'begin' reserved word.");
    }
    else
    {
      pushToErrors(runner->line, "ERROR: Program must start with 'begin' reserved word.");
    }
  }
  if (runner->next != NULL)
  {
    runner = runner->next;
    while (runner->next != NULL)
    {
      // THIS IS WHERE IT SHOULD DO MORE STUFF
      runner = runner->next;
    }
    if (strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "end") != 0)
    {
      if (getErrorHead() == NULL)
      {
        createErrorList(runner->line, "ERROR: Program must end with 'end' reserved word.");
      }
      else
      {
        pushToErrors(runner->line, "ERROR: Program must end with 'end' reserved word.");
      }
    }
  }
  if (getErrorHead() != NULL)
  {
    return false;
  }
  else
  {
    return true;
  }
}
