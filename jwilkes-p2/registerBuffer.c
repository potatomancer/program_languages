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
  if (bufferHead == NULL)
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

void bufferRemoveFromMiddle(bufferNode *node)
{
  printf("bufferRemoveFromMiddle\n");
  bufferNode *head = bufferHead;
  while (head != NULL)
  {
    if (head == node)
    {
      break;
    }
    head = head->next;
  }
  if (head != NULL)
  {
    head->next->last = head->last;
    head->last->next = head->next;
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
