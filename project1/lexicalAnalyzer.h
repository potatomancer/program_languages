#ifndef lexicalAnalyzer
#define lexicalAnalyzer
  #include<stdlib.h>
  #include<stdio.h>
  #include<stdbool.h>
  
  void beginAnalysis(FILE *file);
  int analyzeChar(char c);
  void clearLexeme(int length);

#endif
