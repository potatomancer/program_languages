/* This file creates a linked list to store tokens found in the given text file. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/07/2019
*/

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lexemeNode
{
    int line;
    char word[30];
    char whatAmI[15];
    lexemeNode *next;
};

lexemeNode *head = NULL;
lexemeNode *pointer = NULL;

/* Method to initially create the token linked list */
lexemeNode *createList(int line, char newWord[], char whatAmI[])
{
    printf("Creating Linked List\n");
    head = (lexemeNode *)malloc(sizeof(lexemeNode));
    head->line = line;
    strcpy(head->word, newWord);
    strcpy(head->whatAmI, whatAmI);
    head->next = NULL;
    pointer = head;
    return head;
}

/* Method to push new data into token linked list */
void push(int line, char newWord[], char whatAmI[])
{
    pointer->next = (lexemeNode *)malloc(sizeof(lexemeNode));
    pointer = pointer->next;
    pointer->line = line;
    strcpy(pointer->word, newWord);
    strcpy(pointer->whatAmI, whatAmI);
    pointer->next = NULL;
}

/* Method to print all nodes and node data in token linked list */
void printList()
{
    pointer = head;
    while (pointer != NULL)
    {
        printf("%i: '%s': %s\n", pointer->line, pointer->word, pointer->whatAmI);
        pointer = pointer->next;
    }
}

/* Gets current token based on the iterator’s current position */
char *getCurrentWord()
{
    return pointer->word;
}

/* Gets current identifier based on the iterator’s current position */
char *getCurrentIdentifier()
{
    return pointer->whatAmI;
}

/* Returns head of token linked list */
lexemeNode *getHead()
{
    return head;
}
