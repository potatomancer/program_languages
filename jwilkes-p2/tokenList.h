#ifndef tokenList
#define tokenList
#include <stdlib.h>
#include <stdio.h>

typedef struct lexemeNode lexemeNode;

lexemeNode *createList(int line, char word[], char whatAmI[]);
void pushToken(int line, char newWord[], char whatAmI[]);
void printTokenList();
char *getCurrentIdentifier();
lexemeNode *getTokenHead();

#endif