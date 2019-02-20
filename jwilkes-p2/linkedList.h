#ifndef linkedList
#define linkedList
#include <stdlib.h>
#include <stdio.h>

typedef struct lexemeNode lexemeNode;

lexemeNode *createList(int line, char word[], char whatAmI[]);
void push(int line, char newWord[], char whatAmI[]);
void printList();
char *getCurrentWord();
char *getCurrentIdentifier();
lexemeNode *getHead();
void printIdentifiers();

#endif