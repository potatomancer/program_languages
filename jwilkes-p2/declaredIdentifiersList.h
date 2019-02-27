#ifndef declaredIdentifiersList
#define declaredIdentifiersList
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct declaredNode declaredNode;

declaredNode *createDIList(int line, char word[]);
void pushDI(int line, char newWord[]);
void printDIList();
declaredNode *getDIHead();
bool isIdentifierDeclared();

void printDIListBackwards();

#endif