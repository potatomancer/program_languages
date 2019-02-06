CC=gcc
CFLAGS=-I.
DEPS = queue.h
OBJ = main.o queue.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm run $(OBJ)
