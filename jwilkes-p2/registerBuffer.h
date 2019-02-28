#ifndef registerBuffer
#define registerBuffer
#include <stdlib.h>
#include <stdio.h>

typedef struct bufferNode bufferNode;

bufferNode *createBufferStack(char word[]);
void pushToBuffer(char newWord[]);
void printBufferStack();
bufferNode *getBufferHead();

void printBufferBackwards();
bufferNode *getBufferLast();
char *popFromBuffer();
void bufferRemoveFromMiddle(bufferNode *node);

#endif