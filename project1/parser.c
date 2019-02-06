#include "parser.h"
#include "linkedList.h"
#include "errorList.h"
#include <string.h>
#include <stdbool.h> 

struct lexemeNode { 
  int line;
  char word[30];
  char whatAmI[15];
  lexemeNode *next; 
}; 

char* reservedWords[2] = {"begin", "end"};
char terminalOperators[7] = {'+', '-', '/', '*', '=', '(', ')'};
char delimiter[] = {' ', '\t', ';'};
lexemeNode* parserHead = NULL;
char* types[5] = {"reserved word", "operator", "delimiter", "identifier", "value"};
#define RESWORD "reserved word"
#define OPERATOR "operator"
#define DELIMITER "delimiter"
#define IDENTIFIER "identifier"
#define VALUE "value"

bool isReservedWord(char word[]) {
  int index = 0;
  for (index = 0; index < 2; index++) {
    if (strcmp(reservedWords[index], word) == 0) {
      return true;
    }
  }
  return false;
}

bool isOperator(char c) {
  int i;
  for (i = 0; i < 7; i++) {
    if (c == terminalOperators[i]) {
      return true;
    }
  }
  return false;
}

bool isDelimiter(char c) {
  int i;
  for (i = 0; i < 3; i++) {
    if (c == delimiter[i]) {
      return true;
    }
  }
  return false;
}

void pushToLL(int line, char lexeme[], char whatAmI[]) {
    if (parserHead == NULL) {
      parserHead = createList(line, lexeme, whatAmI);
    } else {
      push(line, lexeme, whatAmI);
    }
}

bool isValidProgram() {
  lexemeNode* runner = getHead();
  if (strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "begin") != 0) {
    if (getErrorHead() == NULL) {
      createErrorList(runner->line, "ERROR: Program must start with 'begin' reserved word.");
    } else {
      pushToErrors(runner->line, "ERROR: Program must start with 'begin' reserved word.");
    }
  }
  if (runner->next != NULL) {
    runner = runner->next;
    while (runner->next != NULL) {
      // THIS IS WHERE IT SHOULD DO MORE STUFF
      runner = runner->next;
    }
    if (strcmp(runner->whatAmI, RESWORD) != 0 || strcmp(runner->word, "end") != 0) {
      if (getErrorHead() == NULL) {
        createErrorList(runner->line, "ERROR: Program must end with 'end' reserved word.");
      } else {
        pushToErrors(runner->line, "ERROR: Program must end with 'end' reserved word.");
      }
    }
  }
  if (getErrorHead() != NULL) {
    return false;
  } else {
    return true;
  }
}
