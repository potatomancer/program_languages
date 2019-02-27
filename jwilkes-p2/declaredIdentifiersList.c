/* This file creates a linked list to store declared identifiers found in the given text file. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/25/2019
*/

#include "declaredIdentifiersList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct declaredNode
{
  int line;
  char word[30];
  declaredNode *next;
};

declaredNode *declaredHead = NULL;
declaredNode *declaredPointer = NULL;

/* Method to initially create the declared identifiers linked list */
declaredNode *createDIList(int line, char newWord[])
{
  declaredHead = (declaredNode *)malloc(sizeof(declaredNode));
  declaredHead->line = line;
  strcpy(declaredHead->word, newWord);
  declaredHead->next = NULL;
  declaredPointer = declaredHead;
  return declaredHead;
}

/* Method to push new data into declared identifiers linked list */
void pushDI(int line, char newWord[])
{
  if (declaredHead == NULL)
  {
    createDIList(line, newWord);
  }
  else
  {
    declaredPointer->next = (declaredNode *)malloc(sizeof(declaredNode));
    declaredPointer = declaredPointer->next;
    declaredPointer->line = line;
    strcpy(declaredPointer->word, newWord);
    declaredPointer->next = NULL;
  }
}

/* Method to print all nodes and node data in declared identifiers linked list */
void printDIList()
{
  declaredPointer = declaredHead;
  while (declaredPointer != NULL)
  {
    printf("%i: '%s'\n", declaredPointer->line, declaredPointer->word);
    declaredPointer = declaredPointer->next;
  }
}

/* Returns head of declared identifiers linked list */
declaredNode *getDIHead()
{
  return declaredHead;
}

bool isIdentifierDeclared(char identifier[])
{
  bool flag = false;
  declaredPointer = declaredHead;
  while (declaredPointer != NULL)
  {
    if (strcmp(declaredPointer->word, identifier) == 0)
    {
      flag = true;
    }
  }
  return flag;
}
