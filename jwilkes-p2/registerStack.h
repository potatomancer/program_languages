#ifndef registerStack
#define registerStack
#include <stdlib.h>
#include <stdio.h>

typedef struct registerNode registerNode;
typedef struct registers registers;
registerNode *
createRegisterStack(char word[]);
void pushToRegister(char newWord[]);
void printRegisterStack();
registerNode *getRegisterHead();
void writeOutRegister(registerNode *start, char *filename);

#endif