run : main.o queue.o
	gcc -o run main.o queue.o -lm 
queue.o : queue.c queue.h
	gcc -c -Wall queue.c
main.o : main.c queue.h 
	gcc -c -Wall main.c
clean :
	rm run main.o queue.o




