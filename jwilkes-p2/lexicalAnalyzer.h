#ifndef lexicalAnalyzer
#define lexicalAnalyzer
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void beginAnalysis(FILE *file);
int analyzeChar(char c);
void clearLexeme(int length);
bool isReservedWord(char word[]);
bool isOperator(char c);
void pushToLL(int line, char lexeme[], char whatAmI[]);
bool isDelimiter(char c);

#endif
