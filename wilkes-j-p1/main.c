#include "errorList.h"
#include "lexicalAnalyzer.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  FILE *file;
  int c;
  if (argc > 1) {
    file = fopen(argv[1], "r");
    if (file == NULL) {
      printf("ERROR: Unable to open file or invalid filename.\n");
      return 0;
    }
    printf("File to examine: %s\n", argv[1]);
    beginAnalysis(file);
    if (isValidProgram()) {
      printf("Program valid!\n");
    } else {
      printf("Program invalid!  Here's why:\n");
      printErrorList();
    }
    fclose(file);
  }
  return 0;
}