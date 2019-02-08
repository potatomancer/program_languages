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

lexemeNode *runner = NULL;

/* Returns result of parsing through program. */
bool isValidProgram()
{
  runner = getHead();
  if (runner == NULL || strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "begin") != 0)
  {
    errorPush(runner->line, "ERROR: Program must start with 'begin' reserved word.");
  }
  else
  {
    while (runner->next != NULL)
    {
      if (strcmp(runner->word, "end"))
      {
        break;
      }
      runner = runner->next;
      assignmentStatement();
    }
    if (runner == NULL || strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "end") != 0)
    {
      errorPush(runner->line, "ERROR: Program must end with 'end' reserved word.");
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
}

void errorPush(int line, char *errorMessage)
{
  if (getErrorHead() == NULL)
  {
    createErrorList(line, errorMessage);
  }
  else
  {
    pushToErrors(line, errorMessage);
  }
}

void assignmentStatement()
{
  char *id = NULL;
  if (strcmp(runner->whatAmI, IDENTIFIER))
  {
    id = runner->word;
    if (runner->next != NULL && runner->next->word == "=")
    {
      runner = runner->next->next;
      if (!expression())
      {
        errorPush(runner->line, "ERROR: Invalid expression.");
      }
      else
      {
        runner = runner->next;
        // runner->word == ";"
      }
    }
    else
    {
      errorPush(runner->line, "ERROR: Invalid assignment statement.");
    }
  }
  else
  {
    errorPush(runner->line, "ERROR: No identifier found.");
  }
}

bool expression()
{
  if (term() && runner->next != NULL)
  {
    while (strcmp(runner->word, "+") || strcmp(runner->word, "-"))
    {
      if (runner->next != NULL)
      {
        runner = runner->next;
        if (!term())
        {
          errorPush(runner->line, "ERROR: Invalid term.");
          return false;
        }
        else if (runner->next != NULL && strcmp(runner->next, ";"))
        {
          return true;
        }
      }
    }
  }
  else
  {
    errorPush(runner->line, "ERROR: Invalid term.");
    return false;
  }
}

bool term()
{
  if (factor() && runner->next != NULL)
  {
    while (strcmp(runner->word, "*") || strcmp(runner->word, "/"))
    {
      if (runner->next != NULL)
      {
        runner = runner->next;
        if (!factor())
        {
          errorPush(runner->line, "ERROR: Invalid factor.");
        }
      }
    }
  }
  else
  {
    errorPush(runner->line, "ERROR: Invalid factor.");
  }
}

bool factor()
{
  if (strcmp(runner->whatAmI, IDENTIFIER) && runner->next != NULL)
  {
    runner = runner->next;
    return true;
  }
  else if (strcmp(runner->whatAmI, VALUE) && runner->next != NULL)
  {
    runner = runner->next;
    return true;
  }
  else if (strcmp(runner->word, "(") && runner->next != NULL)
  {
    runner = runner->next;
    if (runner->next != NULL)
    {
      if (expression() && strcmp(runner->word, ")"))
      {
        runner = runner->next;
        return true;
      }
    }
    else
    {
      errorPush(runner->line, "ERROR: Errant open parathensis.");
      return false;
    }
  }
  else
  {
    errorPush(runner->line, "ERROR: Invalid character or value.");
    return false;
  }
}
