/* This file creates a linked list to store declared identifiers found in the given text file. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/25/2019
*/

#include "declaredIdentifiersList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct declaredNode
{
  int line;
  char word[30];
  declaredNode *next;
};

declaredNode *declaredHead = NULL;
declaredNode *declaredPointer = NULL;

/* Method to initially create the token linked list */
declaredNode *createDeclaredList(int line, char newWord[])
{
  printf("Creating Linked List\n");
  declaredHead = (declaredNode *)malloc(sizeof(declaredNode));
  declaredHead->line = line;
  strcpy(declaredHead->word, newWord);
  declaredHead->next = NULL;
  declaredPointer = declaredHead;
  return declaredHead;
}

/* Method to push new data into token linked list */
void pushDeclared(int line, char newWord[])
{
  if (declaredHead == NULL)
  {
    createDeclaredList(line, newWord);
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

/* Method to print all nodes and node data in token linked list */
void printDeclaredList()
{
  declaredPointer = declaredHead;
  while (declaredPointer != NULL)
  {
    printf("%i: '%s'\n", declaredPointer->line, declaredPointer->word);
    declaredPointer = declaredPointer->next;
  }
}

/* Returns head of token linked list */
declaredNode *getDeclaredHead()
{
  return declaredHead;
}
