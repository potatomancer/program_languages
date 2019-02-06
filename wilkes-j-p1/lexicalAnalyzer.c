#include "lexicalAnalyzer.h"
#include "linkedList.h"
#include "parser.h"
#include "errorList.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int lineno;
char lexeme[30] = "";
FILE *file;
struct Node* LAhead = NULL;
#define COMMENT '~'

void beginAnalysis(FILE *newFile) {
  file = newFile;
  lineno = 1;
  char c;
  int result;
  while ((c = (char) fgetc(file)) != EOF) {
    result = analyzeChar(c);
  }
  printList();
  printf("\n");
}

int analyzeChar(char c) {
  if (c == COMMENT) {
    lexeme[0] = c;
    int i = 1;
    c = (char) fgetc(file);
    while (c != '\n') {
      lexeme[i] = c;
      i++;
      c = (char) fgetc(file);
    }
    pushToLL(lineno, lexeme, "comment");
    lineno++; 
    clearLexeme(strlen(lexeme));
    return 0;
  } else if (isdigit((char) c)) {
    if (strcmp(lexeme, "") == 0 && strcmp(getCurrentIdentifier(), "operator") == 0) {
      lexeme[0] = c;
      int i = 1;
      while (1) {
        c = (char) fgetc(file);
        if (isdigit(c) || c == '.') {
          if (c == '.') {
            int j;
            for (j = 0; j < strlen(lexeme); j++) {
              if (lexeme[j] == '.') {
                if (getErrorHead() == NULL) {
                  createErrorList(lineno, "ERROR: Cannot have more than one dot operator.");
                } else {
                  pushToErrors(lineno, "ERROR: Cannot have more than one dot operator.");
                }
              }
            }
          }
          lexeme[i] = c;
          i++;
        } else {
          ungetc(c, file);
          break;
        }
      }
      pushToLL(lineno, lexeme, "value");
      clearLexeme(strlen(lexeme));
      return c;
    } 
  } else if (isalpha((char) c)) {
    lexeme[0] = c;
    c = (char) fgetc(file);
    int i = 1;
    while(isalnum(c) || c == '_') {
      if (c == '_' && lexeme[i-1] == '_') {
        if (getErrorHead() == NULL) {
          createErrorList(lineno, "ERROR: Cannot have multiple underscores.");
        } else {
          pushToErrors(lineno, "ERROR: Cannot have multiple underscores.");
        }
        break;
      }
      lexeme[i] = c;
      i++;
      c = (char) fgetc(file);
    }
    ungetc(c, file);
    if (isReservedWord(lexeme)) {
      pushToLL(lineno, lexeme, "reserved word");
      clearLexeme(strlen(lexeme));
    } else {
      pushToLL(lineno, lexeme, "identifier");
      clearLexeme(strlen(lexeme));
    }
    return 0;
  } else if (isOperator(c)) {
    lexeme[0] = c;
    pushToLL(lineno, lexeme, "operator");
    clearLexeme(strlen(lexeme));
    return c;
  } else if (isDelimiter(c)) {
    if (c == ';') {
      lexeme[0] = c;
      pushToLL(lineno, lexeme, "delimiter");
      clearLexeme(strlen(lexeme));
    }
    return c;
  } else if (c == '\n') {
    lineno++;
    return c;
  }
}

void clearLexeme(int length) {
  int i;
    for (i = 0; i < length; i ++ ) {
      lexeme[i] = '\0';
    }
}

