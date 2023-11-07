CC=gcc
CFLAGS=-Wall
reconocedor: main.c reconocedor.h
	$(CC) $(CFLAGS) -o main main.c reconocedor_automata.c 
	./main

test: tests.c reconocedor.h
	$(CC) $(CFLAGS) -o test tests.c reconocedor_automata.c 
	./test
