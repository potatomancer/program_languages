/* This file creates a linked list to store tokens found in the given text file. 
 * Author: Joshua Wilkes
 * Version: 2.0
 * Last Updated: 02/25/2019
*/

#include "registerStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct registerNode
{
  int line;
  char word[30];
  char whatAmI[15];
  registerNode *next;
};

registerNode *registerHead = NULL;
registerNode *registerPointer = NULL;

/* Method to initially create the token linked list */
registerNode *createRegisterStack(int line, char newWord[], char whatAmI[])
{
  registerHead = (registerNode *)malloc(sizeof(registerNode));
  registerHead->line = line;
  strcpy(registerHead->word, newWord);
  strcpy(registerHead->whatAmI, whatAmI);
  registerHead->next = NULL;
  registerPointer = registerHead;
  return registerHead;
}

/* Method to push new data into token linked list */
void pushToRegister(int line, char newWord[], char whatAmI[])
{
  if (registerHead == NULL)
  {
    createRegisterStack(line, newWord, whatAmI);
  }
  else
  {
    registerPointer->next = (registerNode *)malloc(sizeof(registerNode));
    registerPointer = registerPointer->next;
    registerPointer->line = line;
    strcpy(registerPointer->word, newWord);
    strcpy(registerPointer->whatAmI, whatAmI);
    registerPointer->next = NULL;
  }
}

/* Method to print all nodes and node data in token linked list */
void printRegisterStack()
{
  registerPointer = registerHead;
  while (registerPointer != NULL)
  {
    printf("%i: '%s': %s\n", registerPointer->line, registerPointer->word, registerPointer->whatAmI);
    registerPointer = registerPointer->next;
  }
}

/* Gets current identifier based on the iterator’s current position */
char *getCurrentRegister()
{
  return registerPointer->whatAmI;
}

/* Returns registerHead of token linked list */
registerNode *getRegisterHead()
{
  return registerHead;
}
