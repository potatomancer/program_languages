#ifndef registerStack
#define registerStack
#include <stdlib.h>
#include <stdio.h>

typedef struct registerNode registerNode;

registerNode *createRegisterStack(char word[]);
void pushToRegister(char newWord[]);
void printRegisterStack();
registerNode *getRegisterHead();

void printRegisterListBackwards();

#endif