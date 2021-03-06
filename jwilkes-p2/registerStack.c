/* This file holds the finished postfix expression generated by the parser. 
 * Author: Joshua Wilkes
 * Version: 1.0
 * Last Updated: 02/28/2019
*/

#include "registerStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct registerNode
{
  char word[20];
  registerNode *next;
  registerNode *last;
};

registerNode *registerHead = NULL;
registerNode *registerPointer = NULL;

struct registers
{
  char R[3];
  bool used;
};

FILE *fp = NULL;

/* Method to initially create the register's linked list */
registerNode *createRegisterStack(char newWord[])
{
  registerHead = (registerNode *)malloc(sizeof(registerNode));
  strcpy(registerHead->word, newWord);
  registerHead->next = NULL;
  registerHead->last = NULL;
  registerPointer = registerHead;
  return registerHead;
}

/* Method to push new data into register's linked list */
void pushToRegister(char newWord[])
{
  if (registerPointer == NULL)
  {
    createRegisterStack(newWord);
  }
  else
  {
    registerNode *newNode = (registerNode *)malloc(sizeof(registerNode));
    registerPointer->next = newNode;
    newNode->last = registerPointer;
    registerPointer = registerPointer->next;
    strcpy(registerPointer->word, newWord);
    registerPointer->next = NULL;
  }
}

/* Method to print all nodes and node data in register's linked list */
void printRegisterStack()
{
  registerNode *printer = registerHead;
  while (printer != NULL)
  {
    if (printer->next == NULL)
    {
      printf("%s\n", printer->word);
      printer = printer->next;
    }
    else
    {
      printf("%s, ", printer->word);
      printer = printer->next;
    }
  }
}

/* Returns registerHead of register's linked list */
registerNode *getRegisterHead()
{
  return registerHead;
}

/* This method takes the generated postfix expressions in the register and generates register based code to evaluate each expression, then it writes it all to a file based on the input file’s name */
void writeOutRegister(registerNode *start, char *filename)
{
  if (fp == NULL)
  {
    fp = fopen(filename, "w+");
  }
  registers *R0 = (registers *)malloc(sizeof(registers));
  strcpy(R0->R, "R0\0");
  R0->used = false;
  registers *R1 = (registers *)malloc(sizeof(registers));
  strcpy(R1->R, "R1\0");
  R1->used = false;
  registers *R2 = (registers *)malloc(sizeof(registers));
  strcpy(R2->R, "R2\0");
  R2->used = false;
  registers *R3 = (registers *)malloc(sizeof(registers));
  strcpy(R3->R, "R3\0");
  R3->used = false;
  registers *regArray[4] = {R0, R1, R2, R3};
  registerNode *originalStart = start;
  char *idAssign = (char *)malloc(30);
  strcpy(idAssign, start->word);
  start = start->next->next;
  while (strcmp(start->word, ";") != 0)
  {
    if (strcmp(start->word, "*") == 0 || strcmp(start->word, "/") == 0 || strcmp(start->word, "+") == 0 || strcmp(start->word, "-") == 0)
    {
      int i1 = 3;
      int i2;
      for (i1 = 3; i1 >= 0; i1--)
      {
        if (regArray[i1]->used)
        {
          for (i2 = i1 - 1; i2 >= 0; i2--)
          {
            if (regArray[i2]->used)
            {
              fprintf(fp, "%s = %s %s %s\n", regArray[i2]->R, regArray[i2]->R, start->word, regArray[i1]->R);
              regArray[i1]->used = false;
              break;
            }
          }
          break;
        }
      }
    }
    else
    {
      int i = 0;
      for (i = 0; i < 4; i++)
      {
        if (!regArray[i]->used)
        {
          regArray[i]->used = true;
          fprintf(fp, "%s = %s\n", regArray[i]->R, start->word);
          break;
        }
      }
    }
    start = start->next;
  }
  fprintf(fp, "%s = R0\n****[", idAssign);
  originalStart = originalStart->next->next;
  while (strcmp(originalStart->word, ";") != 0)
  {
    if (originalStart->next != NULL && strcmp(originalStart->next->word, ";") == 0)
    {
      fprintf(fp, "%s", originalStart->word);
    }
    else
    {
      fprintf(fp, "%s,", originalStart->word);
    }
    originalStart = originalStart->next;
  }
  fprintf(fp, "]****\n");
  if (originalStart->next != NULL && strcmp(originalStart->next->word, "end") != 0)
  {
    originalStart = originalStart->next;
    writeOutRegister(originalStart, filename);
  }
  else
  {
    fclose(fp);
  }
  free(R0);
  free(R1);
  free(R2);
  free(R3);
}
