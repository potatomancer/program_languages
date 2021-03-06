/* This file analyzes a text file one character at a time, identifies tokens, and inserts the identified tokens into the linked list.
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/07/2019
*/

#include "lexicalAnalyzer.h"
#include "linkedList.h"
#include "parser.h"
#include "errorList.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int lineno;
char lexeme[30] = "";
FILE *file;
struct Node *LAhead = NULL;
#define COMMENT '~'

char *reservedWords[2] = {"begin", "end"};
char terminalOperators[7] = {'+', '-', '/', '*', '=', '(', ')'};
char delimiter[] = {' ', '\t', ';'};
lexemeNode *parserHead = NULL;
char *types[5] = {"reserved word", "operator", "delimiter", "identifier", "value"};

/* Begins analysis of the file.  To be called in the main method. */
void beginAnalysis(FILE *newFile)
{
  file = newFile;
  lineno = 1;
  char c;
  int result;
  while ((c = (char)fgetc(file)) != EOF)
  {
    result = analyzeChar(c);
  }
  printf("\n");
}

/* A char is passed in from the file and when it is identified by the method, the rest of the token is gathered, identified, and passed into the linked list */
int analyzeChar(char c)
{
  if (c == COMMENT)
  {
    lexeme[0] = c;
    int i = 1;
    c = (char)fgetc(file);
    while (c != '\n')
    {
      lexeme[i] = c;
      i++;
      c = (char)fgetc(file);
    }
    pushToLL(lineno, lexeme, "comment");
    lineno++;
    clearLexeme(strlen(lexeme));
    return 0;
  }
  else if (isdigit((char)c))
  {
    if (strcmp(lexeme, "") == 0 && strcmp(getCurrentIdentifier(), "operator") == 0)
    {
      lexeme[0] = c;
      int i = 1;
      while (1)
      {
        c = (char)fgetc(file);
        if (isdigit(c) || c == '.')
        {
          if (c == '.')
          {
            int j;
            for (j = 0; j < strlen(lexeme); j++)
            {
              if (lexeme[j] == '.')
              {
                if (getErrorHead() == NULL)
                {
                  createErrorList(lineno, "ERROR: Cannot have more than one dot operator.");
                }
                else
                {
                  pushToErrors(lineno, "ERROR: Cannot have more than one dot operator.");
                }
              }
            }
          }
          lexeme[i] = c;
          i++;
        }
        else
        {
          ungetc(c, file);
          break;
        }
      }
      pushToLL(lineno, lexeme, "value");
      clearLexeme(strlen(lexeme));
      return c;
    }
  }
  else if (isalpha((char)c))
  {
    lexeme[0] = c;
    c = (char)fgetc(file);
    int i = 1;
    while (isalnum(c) || c == '_')
    {
      if (c == '_' && lexeme[i - 1] == '_')
      {
        if (getErrorHead() == NULL)
        {
          createErrorList(lineno, "ERROR: Cannot have multiple underscores.");
        }
        else
        {
          pushToErrors(lineno, "ERROR: Cannot have multiple underscores.");
        }
        break;
      }
      lexeme[i] = c;
      i++;
      c = (char)fgetc(file);
    }
    ungetc(c, file);
    if (isReservedWord(lexeme))
    {
      pushToLL(lineno, lexeme, "reserved word");
      clearLexeme(strlen(lexeme));
    }
    else
    {
      pushToLL(lineno, lexeme, "identifier");
      clearLexeme(strlen(lexeme));
    }
    return 0;
  }
  else if (isOperator(c))
  {
    lexeme[0] = c;
    pushToLL(lineno, lexeme, "operator");
    clearLexeme(strlen(lexeme));
    return c;
  }
  else if (isDelimiter(c))
  {
    if (c == ';')
    {
      lexeme[0] = c;
      pushToLL(lineno, lexeme, "delimiter");
      clearLexeme(strlen(lexeme));
    }
    return c;
  }
  else if (c == '\n')
  {
    lineno++;
    return c;
  }
}

/* Clears the string variable responsible for storing the token to be passed to the linked list */
void clearLexeme(int length)
{
  int i;
  for (i = 0; i < length; i++)
  {
    lexeme[i] = '\0';
  }
}

/* Checks a string against an array of reserved words.  If not found, token is put into linked list as an identifier */
bool isReservedWord(char word[])
{
  int index = 0;
  for (index = 0; index < 2; index++)
  {
    if (strcmp(reservedWords[index], word) == 0)
    {
      return true;
    }
  }
  return false;
}

/* Checks a character against an array of operators. */
bool isOperator(char c)
{
  int i;
  for (i = 0; i < 7; i++)
  {
    if (c == terminalOperators[i])
    {
      return true;
    }
  }
  return false;
}

/* Checks a character against an array of delimiters. */
bool isDelimiter(char c)
{
  int i;
  for (i = 0; i < 3; i++)
  {
    if (c == delimiter[i])
    {
      return true;
    }
  }
  return false;
}

/* Pushes a token into the linked list */
void pushToLL(int line, char lexeme[], char whatAmI[])
{
  if (parserHead == NULL)
  {
    parserHead = createList(line, lexeme, whatAmI);
  }
  else
  {
    push(line, lexeme, whatAmI);
  }
}
