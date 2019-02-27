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
  declaredNode *last;
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
  declaredHead->last = NULL;
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
    declaredNode *newNode = (declaredNode *)malloc(sizeof(declaredNode));
    declaredPointer->next = newNode;
    newNode->last = declaredPointer;
    declaredPointer = declaredPointer->next;
    declaredPointer->line = line;
    strcpy(declaredPointer->word, newWord);
    declaredPointer->next = NULL;
  }
}

/* Method to print all nodes and node data in declared identifiers linked list */
void printDIList()
{
  declaredNode *printer = declaredHead;
  while (printer->next != NULL)
  {
    printf("%s, ", printer->word);
    printer = printer->next;
  }
  printer = printer->next;
  printf("%s\n", printer->word);
}

void printDIListBackwards()
{
  declaredNode *printer = declaredPointer;
  while (printer->last != NULL)
  {
    printf("%s, ", printer->word);
    printer = printer->last;
  }
  printer = printer->last;
  printf("%s\n", printer->word);
}

/* Returns head of declared identifiers linked list */
declaredNode *getDIHead()
{
  return declaredHead;
}

bool isIdentifierDeclared(char identifier[])
{
  bool flag = false;
  declaredNode *mover = declaredHead;
  while (mover != NULL)
  {
    if (strcmp(mover->word, identifier) == 0)
    {
      flag = true;
    }
  }
  return flag;
}
