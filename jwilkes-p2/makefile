CC=gcc
CFLAGS=-I.
DEPS = lexicalAnalyzer.h parser.h tokenList.h errorList.h declaredIdentifiersList.h registerStack.h registerBuffer.h
OBJ = main.o lexicalAnalyzer.o parser.o tokenList.o errorList.o declaredIdentifiersList.o registerStack.o registerBuffer.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm run $(OBJ)
