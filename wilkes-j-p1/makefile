CC=gcc
CFLAGS=-I.
DEPS = lexicalAnalyzer.h parser.h linkedList.h errorList.h
OBJ = main.o lexicalAnalyzer.o parser.o linkedList.o errorList.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm run $(OBJ)
