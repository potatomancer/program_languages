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

declaredNode *head = NULL;
declaredNode *pointer = NULL;

/* Method to initially create the token linked list */
declaredNode *createDeclaredList(int line, char newWord[])
{
  printf("Creating Linked List\n");
  head = (declaredNode *)malloc(sizeof(declaredNode));
  head->line = line;
  strcpy(head->word, newWord);
  head->next = NULL;
  pointer = head;
  return head;
}

/* Method to push new data into token linked list */
void pushDeclared(int line, char newWord[])
{
  pointer->next = (declaredNode *)malloc(sizeof(declaredNode));
  pointer = pointer->next;
  pointer->line = line;
  strcpy(pointer->word, newWord);
  pointer->next = NULL;
}

/* Method to print all nodes and node data in token linked list */
void printDeclaredList()
{
  pointer = head;
  while (pointer != NULL)
  {
    printf("%i: '%s'\n", pointer->line, pointer->word);
    pointer = pointer->next;
  }
}

/* Returns head of token linked list */
declaredNode *getDeclaredHead()
{
  return head;
}
