#ifndef registerStack
#define registerStack
#include <stdlib.h>
#include <stdio.h>

typedef struct registerNode registerNode;

registerNode *createRegisterStack(int line, char word[], char whatAmI[]);
void pushToRegister(int line, char newWord[], char whatAmI[]);
void printRegisterStack();
char *getCurrentRegister();
registerNode *getRegisterHead();

#endif