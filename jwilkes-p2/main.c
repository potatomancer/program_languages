#include "errorList.h"
#include "tokenList.h"
#include "lexicalAnalyzer.h"
#include "declaredIdentifiersList.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  printf("**********************\nStarting program.\n");
  FILE *file;
  int c;

  pushDI(0, "1");
  pushDI(0, "2");
  pushDI(0, "3");
  pushDI(0, "4");
  pushDI(0, "5");
  pushDI(0, "6");
  pushDI(0, "7");
  printDIList();
  printDIListBackwards();

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
      printf("Program valid!\n");
      printDIList();
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