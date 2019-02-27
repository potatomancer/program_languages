#ifndef parser
#define parser
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isValidProgram();
void assignmentStatement();
bool expression();
bool term();
bool factor();
void skipComments();
void declarationStatement();
void beginRegisterCalculations();

#endif
