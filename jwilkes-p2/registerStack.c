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
  char word[30];
  registerNode *next;
  registerNode *last;
};

registerNode *registerHead = NULL;
registerNode *registerPointer = NULL;

/* Method to initially create the token linked list */
registerNode *createRegisterStack(char newWord[])
{
  registerHead = (registerNode *)malloc(sizeof(registerNode));
  strcpy(registerHead->word, newWord);
  registerHead->next = NULL;
  registerHead->last = NULL;
  registerPointer = registerHead;
  return registerHead;
}

/* Method to push new data into token linked list */
void pushToRegister(char newWord[])
{
  if (registerHead == NULL)
  {
    createRegisterStack(newWord);
  }
  else
  {

    registerNode *newNode = (registerNode *)malloc(sizeof(registerNode));
    registerPointer->next = newNode;
    newNode->last = registerPointer;
    registerPointer = registerPointer->next;
    strcpy(registerPointer->word, newWord);
    registerPointer->next = NULL;
  }
}

/* Method to print all nodes and node data in token linked list */
void printRegisterStack()
{
  registerNode *printer = registerHead;
  while (printer != NULL)
  {
    printf("%s, ", printer->word);
    printer = printer->next;
  }
}

void printRegisterListBackwards()
{
  registerNode *printer = registerHead;
  while (printer != NULL)
  {
    printf("%s, ", printer->word);
    printer = printer->last;
  }
  printf("\n");
}

/* Returns registerHead of token linked list */
registerNode *getRegisterHead()
{
  return registerHead;
}
