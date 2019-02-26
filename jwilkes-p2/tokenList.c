/* This file creates a linked list to store tokens found in the given text file. 
 * Author: Joshua Wilkes
 * Version: 2.0
 * Last Updated: 02/25/2019
*/

#include "tokenList.h"
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

lexemeNode *tokenHead = NULL;
lexemeNode *tokenPointer = NULL;

/* Method to initially create the token linked list */
lexemeNode *createTokenList(int line, char newWord[], char whatAmI[])
{
    tokenHead = (lexemeNode *)malloc(sizeof(lexemeNode));
    tokenHead->line = line;
    strcpy(tokenHead->word, newWord);
    strcpy(tokenHead->whatAmI, whatAmI);
    tokenHead->next = NULL;
    tokenPointer = tokenHead;
    return tokenHead;
}

/* Method to push new data into token linked list */
void pushToken(int line, char newWord[], char whatAmI[])
{
    if (tokenHead == NULL)
    {
        createTokenList(line, newWord, whatAmI);
    }
    else
    {
        tokenPointer->next = (lexemeNode *)malloc(sizeof(lexemeNode));
        tokenPointer = tokenPointer->next;
        tokenPointer->line = line;
        strcpy(tokenPointer->word, newWord);
        strcpy(tokenPointer->whatAmI, whatAmI);
        tokenPointer->next = NULL;
    }
}

/* Method to print all nodes and node data in token linked list */
void printTokenList()
{
    tokenPointer = tokenHead;
    while (tokenPointer != NULL)
    {
        printf("%i: '%s': %s\n", tokenPointer->line, tokenPointer->word, tokenPointer->whatAmI);
        tokenPointer = tokenPointer->next;
    }
}

/* Gets current identifier based on the iterator’s current position */
char *getCurrentIdentifier()
{
    return tokenPointer->whatAmI;
}

/* Returns tokenHead of token linked list */
lexemeNode *getTokenHead()
{
    return tokenHead;
}
