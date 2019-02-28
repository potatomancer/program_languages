#include "errorList.h"
#include "tokenList.h"
#include "lexicalAnalyzer.h"
#include "declaredIdentifiersList.h"
#include "registerStack.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  printf("**********************\nStarting program.\n");
  FILE *file;
  int c;
  if (argc > 1)
  {
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
      printf("ERROR: Unable to open file or invalid filename.\n");
      return 0;
    }
    printf("File to examine: %s\n", argv[1]);
    beginAnalysis(file);
    if (isValidProgram())
    {
      char *fncopy = (char *)malloc(30);
      strcpy(fncopy, argv[1]);
      int fnlength = strlen(argv[1]);
      fncopy[fnlength - 3] = 'o';
      fncopy[fnlength - 2] = 'u';
      fncopy[fnlength - 1] = 't';
      printf("Program valid! - Output is in file %s\n", fncopy);
      writeOutRegister(getRegisterHead(), fncopy);
    }
    else
    {
      printf("Program invalid!  Here's why:\n");
      printErrorList();
    }
    fclose(file);
    printf("**********************\n\n");
  }
  return 0;
}