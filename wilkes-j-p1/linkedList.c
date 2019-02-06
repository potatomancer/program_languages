#include "linkedList.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

  struct lexemeNode
  { 
    int line;
    char word[30];
    char whatAmI[15];
    lexemeNode *next; 
  }; 

lexemeNode* head = NULL;
lexemeNode* pointer = NULL;

lexemeNode* createList(int line, char newWord[], char whatAmI[]) {
    printf("Creating Linked List\n");
    head = (lexemeNode*) malloc(sizeof(lexemeNode));
    head->line = line; 
    strcpy(head->word, newWord);
    strcpy(head->whatAmI, whatAmI);
    head->next = NULL;
    pointer = head;
    return head;
}

void push(int line, char newWord[], char whatAmI[]) {
    pointer->next = (lexemeNode*) malloc(sizeof(lexemeNode));
    pointer = pointer->next;
    pointer->line = line;
    strcpy(pointer->word, newWord);
    strcpy(pointer->whatAmI, whatAmI);
    pointer->next = NULL;
}

void printList() {
    pointer = head;
    while (pointer != NULL) {
        printf("%i: '%s': %s\n", pointer->line, pointer->word, pointer->whatAmI);
        pointer = pointer->next;
    }
}

char* getCurrentWord() {
    return pointer->word;
}

char* getCurrentIdentifier() {
    return pointer->whatAmI;
}

lexemeNode* getHead() {
    return head;
}
