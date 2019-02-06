#ifndef parser
#define parser
  #include<stdlib.h>
  #include<stdio.h>
  #include<stdbool.h>

  bool isReservedWord(char word[]);
  bool isOperator(char c);
  void pushToLL(int line, char lexeme[], char whatAmI[]);
  bool isDelimiter(char c);
  bool isValidProgram();

#endif
