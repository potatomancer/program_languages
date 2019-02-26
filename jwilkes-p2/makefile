CC=gcc
CFLAGS=-I.
DEPS = lexicalAnalyzer.h parser.h tokenList.h errorList.h declaredIdentifiersList.h
OBJ = main.o lexicalAnalyzer.o parser.o tokenList.o errorList.o declaredIdentifiersList.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm run $(OBJ)
