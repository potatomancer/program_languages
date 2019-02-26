#ifndef declaredIdentifiersList
#define declaredIdentifiersList
#include <stdlib.h>
#include <stdio.h>

typedef struct declaredNode declaredNode;

declaredNode *createDeclaredList(int line, char word[]);
void pushDeclared(int line, char newWord[]);
void printDeclaredList();
declaredNode *getDeclaredHead();

#endif