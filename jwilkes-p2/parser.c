/* This file iterates through the token linked list and checks if the order of tokens/types is valid based on the rules set forth in the project. 
 * Author: Joshua Wilkes
 * Version: 2.0
 * Last Updated: 02/28/2019
*/

#include "parser.h"
#include "tokenList.h"
#include "errorList.h"
#include "declaredIdentifiersList.h"
#include "registerStack.h"
#include "lexicalAnalyzer.h"
#include "registerBuffer.h"
#include <string.h>
#include <stdbool.h>

struct lexemeNode
{
  int line;
  char word[30];
  char whatAmI[15];
  lexemeNode *next;
};
struct bufferNode
{
  char word[30];
  bufferNode *next;
  bufferNode *last;
};

#define RESWORD "reserved word"
#define INTEGER "int"
#define END "end"
#define OPERATOR "operator"
#define DELIMITER "delimiter"
#define IDENTIFIER "identifier"
#define VALUE "value"
#define COMMENT "comment"
#define terminalOperatorsWithPrecedenceCount 7
char *terminalOperatorsWithPrecedence[terminalOperatorsWithPrecedenceCount] = {
    "(",
    "/",
    "*",
    "+",
    "-",
    ")",
    "=",
};

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
    bool decStatGotCalled = false;
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
        decStatGotCalled = true;
      }
      skipComments();
      if (strcmp(runner->whatAmI, IDENTIFIER) == 0 && decStatGotCalled)
      {
        printf("ass stat\n");
        assignmentStatement();
      }
      else if (!decStatGotCalled)
      {
        break;
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
    getFirstAssignmentStatement();
    registerCalculation();
    printRegisterStack();
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
    printf("132: %s\n", runner->word);
    runner = runner->next->next;
    if (expression())
    {
      printf("136: expression was true\n");
      runner = runner->next;
      // runner->word == ";"
    }
    else
    {
      printf("142: error");
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
  if (term() && runner->next != NULL)
  {
    printf("165: %s\n", runner->word);
    while ((strcmp(runner->word, "+") == 0) || (strcmp(runner->word, "-") == 0))
    {
      printf("168: %s\n", runner->word);
      if (runner->next != NULL)
      {
        runner = runner->next;
        if (!term())
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

void getFirstAssignmentStatement()
{
  runner = getTokenHead();
  while (strcmp(runner->next->word, "=") != 0)
  {
    runner = runner->next;
  }
}

void registerCalculation()
{
  // Identifier
  pushToRegister(runner->word);
  runner = runner->next;
  // "="
  pushToRegister(runner->word);
  runner = runner->next;

  while (strcmp(runner->word, ";") != 0 || runner != NULL)
  {
    evaluateTokenForPostfix();
  }
  // ";"
  if (runner != NULL)
  {
    pushToRegister(runner->word);
    printf("PRINTING LIST\n");
    printRegisterStack();
    runner = runner->next;
    if (strcmp(runner->whatAmI, IDENTIFIER) == 0)
    {
      registerCalculation();
    }
  }
}

void evaluateTokenForPostfix()
{
  printf("Evaluating: %s, What Am I: %s\n", runner->word, runner->whatAmI);
  if (strcmp(runner->whatAmI, IDENTIFIER) == 0 || strcmp(runner->whatAmI, VALUE) == 0)
  {
    pushToRegister(runner->word);
  }
  else if (strcmp(runner->whatAmI, OPERATOR) == 0)
  {
    bufferNode *bufferLast = getBufferLast();
    printf("bufferLast: %s\n", bufferLast->word);
    if (bufferLast == NULL)
    {
      printf("%s: bufferLast == NULL\n", runner->word);
      pushToBuffer(runner->word);
    }
    else if (strcmp(runner->word, "(") == 0)
    {
      printf("%s: strcmp(runner->word, ( ) == 0\n", runner->word);
      pushToBuffer(runner->word);
    }
    else if (strcmp(runner->word, ")") == 0)
    {
      printf("runner: %s, buffer: %s: strcmp(runner->word, ) ) == 0\n", runner->word, bufferLast->word);
      while (strcmp(bufferLast->word, "(") != 0)
      {
        printf(")-while: %s\n", bufferLast->word);
        pushToRegister(popFromBuffer());
        bufferLast = getBufferLast();
      }
      bufferRemoveFromMiddle(bufferLast);
    }
    else if (indexOf(runner->word) > indexOf(bufferLast->word))
    {
      printf("%s: indexOf(runner->word) > indexOf(bufferLast->word)\n", runner->word);
      pushToBuffer(runner->word);
    }
    else
    {
      printf("%s: else\n", runner->word);
      while (bufferLast != NULL || strcmp(bufferLast->word, "(") != 0)
      {
        if (indexOf(bufferLast->word) > indexOf(runner->word))
        {
          pushToRegister(popFromBuffer());
        }
        else
        {
          break;
        }
        bufferLast = getBufferLast();
      }
      pushToBuffer(runner->word);
    }
  }

  // Follow algorithm to create postfix expression
  /* 
    1. Scan the infix expression from left to right.
    2. If the scanned character is an operand, output it.
    3. Else,
    …..3.1 If the precedence of the scanned operator is greater than the precedence of the operator in the stack(or the stack is empty or the stack contains a ‘(‘ ), push it.
    …..3.2 Else, Pop all the operators from the stack which are greater than or equal to in precedence than that of the scanned operator. After doing that Push the scanned operator to the stack. (If you encounter parenthesis while popping then stop there and push the scanned operator in the stack.)
    4. If the scanned character is an ‘(‘, push it to the stack.
    5. If the scanned character is an ‘)’, pop the stack and and output it until a ‘(‘ is encountered, and discard both the parenthesis.
    6. Repeat steps 2-6 until infix expression is scanned.
    7. Print the output
    8. Pop and output from the stack until it is not empty. */
  if (runner->next != NULL && strcmp(runner->next->word, ";") == 0 && getBufferLast() != NULL)
  {
    printf("runner->next->word: %s, bufferLast->word: %s\n", runner->next->word, getBufferLast()->word);
    pushToRegister(popFromBuffer());
  }
  runner = runner->next;
}

int indexOf(char operator[])
{
  int returnIndex = 0;
  for (returnIndex = 0; returnIndex < terminalOperatorsWithPrecedenceCount; returnIndex++)
  {
    if (strcmp(terminalOperatorsWithPrecedence[returnIndex], operator) == 0)
    {
      return returnIndex;
    }
  }
  printf("operator: %s, index: %i\n", operator, returnIndex);
  return returnIndex;
}
