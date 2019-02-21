/* This file creates a linked list to store errors found in the code. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/07/2019
*/

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

errorNode *errorHead = NULL;
errorNode *errorPointer = NULL;

/* Method to initially create the error linked list */
errorNode *createErrorList(int line, char message[])
{
    printf("Creating Error List\nLine %i: %s\n", line, message);
    errorHead = (errorNode *)malloc(sizeof(errorNode));
    errorHead->line = line;
    strcpy(errorHead->message, message);
    errorHead->next = NULL;
    errorPointer = errorHead;
    return errorHead;
}

/* Method to push new data into error linked list */
void pushToErrors(int line, char message[])
{
    errorPointer->next = (errorNode *)malloc(sizeof(errorNode));
    errorPointer = errorPointer->next;
    errorPointer->line = line;
    strcpy(errorPointer->message, message);
    errorPointer->next = NULL;
}

/* Method to print all nodes and node data in error linked list */
void printErrorList()
{
    errorPointer = errorHead;
    while (errorPointer != NULL)
    {
        printf("Line %i: %s\n", errorPointer->line, errorPointer->message);
        errorPointer = errorPointer->next;
    }
}

/* Returns head of error linked list */
errorNode *getErrorHead()
{
    return errorHead;
}