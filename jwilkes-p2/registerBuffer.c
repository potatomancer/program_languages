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

/* Method to initially create the buffer's linked list */
bufferNode *createBufferStack(char newWord[])
{
  bufferHead = (bufferNode *)malloc(sizeof(bufferNode));
  strcpy(bufferHead->word, newWord);
  bufferHead->next = NULL;
  bufferHead->last = NULL;
  bufferPointer = bufferHead;
  return bufferHead;
}

/* Method to push new data into buffer's linked list */
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

/* Method to remove the last data item from buffer’s linked list */
char *popFromBuffer()
{
  char *returnWord = (char *)malloc(30);
  strcpy(returnWord, bufferPointer->word);
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
  return returnWord;
}

/* Method to remove a data item from the middle of the buffer’s linked list */
void bufferRemoveFromMiddle(char *word)
{
  bufferNode *pointer = bufferPointer;
  while (pointer != NULL)
  {
    if (pointer->word == word)
    {
      break;
    }
    pointer = pointer->last;
  }
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
  if (pointer->next != NULL)
  {
    while (pointer->next != NULL)
    {
      pointer = pointer->next;
    }
    bufferPointer = pointer;
  }
  else
  {
    bufferPointer = pointer->last;
  }
}

/* Method to print all buffer data buffer's linked list */
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

/* Returns bufferHead of buffer's linked list */
bufferNode *getBufferHead()
{
  return bufferHead;
}

/* Returns bufferHead of buffer's linked list */
bufferNode *getBufferLast()
{
  return bufferPointer;
}
