#ifndef parser
#define parser
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isValidProgram();
void errorPush(int line, char *errorMessage);
void assignmentStatement();
bool expression();
bool term();
bool factor();

#endif
