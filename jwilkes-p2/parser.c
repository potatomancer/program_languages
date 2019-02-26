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
#define INTEGER "int"
#define END "end"
#define OPERATOR "operator"
#define DELIMITER "delimiter"
#define IDENTIFIER "identifier"
#define VALUE "value"
#define COMMENT "comment"

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
    runner = runner->next;
    while (runner->next != NULL)
    {
      if (strcmp(runner->word, END) == 0)
      {
        break;
      }
      skipComments();
      while (strcmp(runner->word, INTEGER) == 0)
      {
        printf("start dec statement\n");
        declarationStatement();
        printf("end dec statement\n");
      }
      printf("start comment check\n");
      skipComments();
      while (strcmp(runner->whatAmI, IDENTIFIER) == 0)
      {
        printf("Assignment Statement\n");
        assignmentStatement();
      }
      if (strcmp(runner->word, END) == 0)
      {
        break;
      }
    }
    if (runner == NULL || strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, END) != 0)
    {
      errorPush(runner->line, "ERROR: Program must end with 'end' reserved word.");
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

void skipComments()
{
  while (strcmp(runner->whatAmI, COMMENT) == 0)
  {
    runner = runner->next;
  }
}

/* Pushes an error with a message into the error linked list */
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

void declarationStatement()
{
  printf("What is it tho: %s\n", runner->next->whatAmI);
  if (strcmp(runner->next->whatAmI, IDENTIFIER) == 0)
  {
    runner = runner->next;
    //add runner to declared identifiers linked list
    printf("Check for comma or semi: %s\n", runner->next->word);
    if (runner->next != NULL && strcmp(runner->next->word, ",") == 0)
    {
      runner = runner->next;
      declarationStatement();
    }
    else if (runner->next != NULL && strcmp(runner->next->word, "=") == 0)
    {
      errorPush(runner->line, "ERROR: Assignment is not allowed in declaration statement.");
      while (strcmp(runner->next->word, ";") == 0 || strcmp(runner->next->word, END) == 0)
      {
        runner = runner->next;
      }
    }
    else if (runner->next != NULL && strcmp(runner->next->word, ";") == 0)
    {
      runner = runner->next;
      printf("After semi: %s\n", runner->next->word);
      if (runner->next != NULL)
      {
        runner = runner->next;
      }
    }
    else
    {
      printf("Failed on inner error: %s\n", runner->next->word);
      errorPush(runner->line, "ERROR: Invalid declaration statement.");
    }
  }
  else
  {
    printf("Failed on outer error: %s\n", runner->next->word);
    errorPush(runner->line, "ERROR: Invalid declaration statement.");
  }
}

/* Begins the process for identifying an assignment statement in program */
void assignmentStatement()
{
  char *id = NULL;
  /*   if (strcmp(runner->word, INTEGER) == 0)
  {
    runner = runner->next;
  } */
  if (strcmp(runner->whatAmI, IDENTIFIER) == 0)
  {
    id = runner->word;
    if (runner->next != NULL && (strcmp(runner->next->word, "=") == 0))
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

/* Identifies an expression in an assignment statement */
bool expression()
{
  if (term() && (strcmp(runner->word, ";")) && runner->next != NULL)
  {
    while ((strcmp(runner->word, "+") == 0) || (strcmp(runner->word, "-") == 0))
    {
      if (runner->next != NULL)
      {
        runner = runner->next;
        if (!term())
        {
          errorPush(runner->line, "ERROR: Invalid term 1.");
          return false;
        }
        else if (runner->next != NULL && (strcmp(runner->word, ";") == 0))
        {
          return true;
        }
      }
    }
  }
  else if (runner->next != NULL && (strcmp(runner->word, ";") == 0))
  {
    return true;
  }
  else
  {
    errorPush(runner->line, "ERROR: Invalid term 2.");
    return false;
  }
}

/* Identifies a term in an expression */
bool term()
{
  if (factor() && runner->next != NULL)
  {
    while ((strcmp(runner->word, "*") == 0) || (strcmp(runner->word, "/") == 0))
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
    return true;
  }
  else
  {
    errorPush(runner->line, "ERROR: Invalid factor.");
    return false;
  }
}

/* Identifies a factor in a term */
bool factor()
{
  if ((strcmp(runner->whatAmI, IDENTIFIER) == 0) && runner->next != NULL)
  {
    runner = runner->next;
    return true;
  }
  else if ((strcmp(runner->whatAmI, VALUE) == 0) && runner->next != NULL)
  {
    runner = runner->next;
    return true;
  }
  else if ((strcmp(runner->word, "(") == 0) && runner->next != NULL)
  {
    runner = runner->next;
    if (runner->next != NULL)
    {
      if (expression() && (strcmp(runner->word, ")") == 0))
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
