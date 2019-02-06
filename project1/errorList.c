#include <errorList.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct errorNode
{ 
  int line;
  char message[75];
  errorNode *next; 
}; 

errorNode* errorHead = NULL;
errorNode* errorPointer = NULL;

errorNode* createErrorList(int line, char message[]) {
    printf("Creating Error List\n");
    errorHead = (errorNode*) malloc(sizeof(errorNode)); 
    errorHead->line = line;
    strcpy(errorHead->message, message);
    errorHead->next = NULL;
    errorPointer = errorHead;
    return errorHead;
}

void pushToErrors(int line, char message[]) {
    errorPointer->next = (errorNode*) malloc(sizeof(errorNode));
    errorPointer = errorPointer->next;
    errorPointer->line = line;
    strcpy(errorPointer->message, message);
    errorPointer->next = NULL;
}

void printErrorList() {
    errorPointer = errorHead;
    while (errorPointer != NULL) {
        printf("Line %i: %s\n", errorPointer->line, errorPointer->message);
        errorPointer = errorPointer->next;
    }
}

errorNode* getErrorHead() {
    return errorHead;
}