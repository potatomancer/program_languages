/* This file is a buffer for the register stack to assist in creating a postfix expression. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/28/2019
*/

#include "registerBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bufferNode
{
  char word[30];
  bufferNode *next;
  bufferNode *last;
};

bufferNode *bufferHead = NULL;
bufferNode *bufferPointer = NULL;

/* Method to initially create the token linked list */
bufferNode *createBufferStack(char newWord[])
{
  bufferHead = (bufferNode *)malloc(sizeof(bufferNode));
  strcpy(bufferHead->word, newWord);
  bufferHead->next = NULL;
  bufferHead->last = NULL;
  bufferPointer = bufferHead;
  return bufferHead;
}

/* Method to push new data into token linked list */
void pushToBuffer(char newWord[])
{
  if (bufferPointer == NULL)
  {
    createBufferStack(newWord);
  }
  else
  {
    bufferNode *newNode = (bufferNode *)malloc(sizeof(bufferNode));
    bufferPointer->next = newNode;
    newNode->last = bufferPointer;
    bufferPointer = bufferPointer->next;
    strcpy(bufferPointer->word, newWord);
    bufferPointer->next = NULL;
  }
}

char *popFromBuffer()
{
  char *returnWord = bufferPointer->word;
  if (bufferPointer->last == NULL)
  {
    bufferPointer = NULL;
  }
  else
  {
    bufferPointer = bufferPointer->last;
    free(bufferPointer->next);
    bufferPointer->next = NULL;
  }
  printf("popFromBuffer: %s\n", bufferPointer->word);
  return returnWord;
}

void bufferRemoveFromMiddle(char *word)
{
  printf("bufferRemoveFromMiddle\n");
  bufferNode *pointer = bufferPointer;
  while (pointer != NULL)
  {
    if (pointer->word == word)
    {
      printf("I'm one step closer to the edge: %s\n", pointer->word);
      break;
    }
    pointer = pointer->last;
  }
  printf("And I'm about to break.  I already broke: %s\n", pointer->word);
  if (pointer != NULL)
  {
    if (pointer->next != NULL)
    {
      pointer->next->last = pointer->last;
    }
    if (pointer->last != NULL)
    {
      pointer->last->next = pointer->next;
    }
  }
}

/* Method to print all nodes and node data in token linked list */
void printBufferStack()
{
  bufferNode *printer = bufferHead;
  while (printer != NULL)
  {
    if (printer->next == NULL)
    {
      printf("%s\n", printer->word);
      printer = printer->next;
    }
    else
    {
      printf("%s, ", printer->word);
      printer = printer->next;
    }
  }
}

void printBufferBackwards()
{
  bufferNode *printer = bufferHead;
  while (printer != NULL)
  {
    if (printer->last == NULL)
    {
      printf("%s\n", printer->word);
      printer = printer->next;
    }
    else
    {
      printf("%s, ", printer->word);
      printer = printer->last;
    }
  }
}

/* Returns bufferHead of token linked list */
bufferNode *getBufferHead()
{
  return bufferHead;
}

/* Returns bufferHead of token linked list */
bufferNode *getBufferLast()
{
  return bufferPointer;
}
