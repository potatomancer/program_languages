/* This file iterates through the token linked list and checks if the order of tokens/types is valid based on the rules set forth in the project. 
 * Author: Joshua Wilkes
 * Version: 2.0
 * Last Updated: 02/25/2019
*/

#include "parser.h"
#include "tokenList.h"
#include "errorList.h"
#include "declaredIdentifiersList.h"
#include "registerStack.h"
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
  runner = getTokenHead();
  if (runner == NULL || strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "begin") != 0)
  {
    pushError(runner->line, "ERROR: Program must start with 'begin' reserved word.");
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
      if (strcmp(runner->word, INTEGER) == 0)
      {
        printf("dec stat\n");
        declarationStatement();
      }
      skipComments();
      if (strcmp(runner->whatAmI, IDENTIFIER) == 0)
      {
        printf("ass stat\n");
        assignmentStatement();
      }
    }
    if (runner == NULL || strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, END) != 0)
    {
      pushError(runner->line, "ERROR: Program must end with 'end' reserved word.");
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

/* Skips all lines of comments during parsing */
void skipComments()
{
  while (strcmp(runner->whatAmI, COMMENT) == 0)
  {
    runner = runner->next;
  }
}

/* Identifies a declaration statement and inserts valid identifies into declared identifiers linked list */
void declarationStatement()
{
  if (strcmp(runner->next->whatAmI, IDENTIFIER) == 0)
  {
    runner = runner->next;
    pushDI(runner->line, runner->word);
    if (runner->next != NULL && strcmp(runner->next->word, ",") == 0)
    {
      runner = runner->next;
      declarationStatement();
    }
    else if (runner->next != NULL && strcmp(runner->next->word, "=") == 0)
    {
      pushError(runner->line, "ERROR: Assignment is not allowed in declaration statement.");
      while (strcmp(runner->next->word, ";") == 0 || strcmp(runner->next->word, END) == 0)
      {
        runner = runner->next;
      }
    }
    else if (runner->next != NULL && strcmp(runner->next->word, ";") == 0)
    {
      runner = runner->next;
      if (runner->next != NULL)
      {
        runner = runner->next;
      }
    }
    else
    {
      pushError(runner->line, "ERROR: Invalid declaration statement.");
    }
  }
  else
  {
    pushError(runner->line, "ERROR: Invalid declaration statement.");
  }
}

/* Begins the process for identifying an assignment statement in program */
void assignmentStatement()
{
  if (runner->next != NULL && (strcmp(runner->next->word, "=") == 0))
  {
    printf("=\n");
    runner = runner->next->next;
    if (expression())
    {
      printf("expression was true\n");
      runner = runner->next;
      // runner->word == ";"
    }
    else
    {
      pushError(runner->line, "ERROR: Invalid expression.");
    }
  }
  else
  {
    pushError(runner->line, "ERROR: Invalid assignment statement.");
    while (strcmp(runner->next->word, ";") != 0)
    {
      runner = runner->next;
    }
    runner = runner->next;
    if (runner->next != NULL)
    {
      runner = runner->next;
    }
  }
}

/* Identifies an expression in an assignment statement */
bool expression()
{
  if (term() && (strcmp(runner->word, ";") == 0) && runner->next != NULL)
  {
    printf("%s\n", runner->word);
    while ((strcmp(runner->word, "+") == 0) || (strcmp(runner->word, "-") == 0))
    {
      printf("%s\n", runner->word);
      if (runner->next != NULL)
      {
        runner = runner->next;
        if (term())
        {
          pushError(runner->line, "ERROR: Invalid term 1.");
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
    printf("%s\n", runner->word);
    pushError(runner->line, "ERROR: Invalid term 2.");
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
      printf("%s\n", runner->word);
      if (runner->next != NULL)
      {
        runner = runner->next;
        if (!factor())
        {
          pushError(runner->line, "ERROR: Invalid factor.");
        }
      }
    }
    return true;
  }
  else
  {
    pushError(runner->line, "ERROR: Invalid factor 2.");
    return false;
  }
}

/* Identifies a factor in a term */
bool factor()
{
  if ((strcmp(runner->whatAmI, IDENTIFIER) == 0) && runner->next != NULL)
  {
    printf("IDentifier %s\n", runner->word);
    runner = runner->next;
    return true;
  }
  else if ((strcmp(runner->whatAmI, VALUE) == 0) && runner->next != NULL)
  {
    printf("value %s\n", runner->word);
    runner = runner->next;
    return true;
  }
  else if ((strcmp(runner->word, "(") == 0) && runner->next != NULL)
  {
    printf("(\n");
    runner = runner->next;
    if (runner->next != NULL)
    {
      if (expression() && (strcmp(runner->word, ")") == 0))
      {
        printf(")\n");
        runner = runner->next;
        return true;
      }
    }
    else
    {
      pushError(runner->line, "ERROR: Errant open parathensis.");
      return false;
    }
  }
  else
  {
    pushError(runner->line, "ERROR: Invalid character or value.");
    return false;
  }
}
