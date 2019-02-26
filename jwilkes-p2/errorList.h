#ifndef errorList
#define errorList
#include <stdlib.h>
#include <stdio.h>

typedef struct errorNode errorNode;

errorNode *createErrorList(int line, char message[]);
void pushError(int line, char message[]);
void printErrorList();
errorNode *getErrorHead();

#endif