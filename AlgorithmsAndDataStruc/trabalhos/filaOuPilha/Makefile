CC = gcc
program = main

all: main.c ./pilha/pilha.c ./pilha/pilha.h ./fila/fila.c ./fila/fila.h
	$(CC) -o $(program) main.c ./pilha/pilha.c ./fila/fila.c

clean:
	rm -r */*.o $(program)

run:
	$(CC) -o $(program) main.c ./pilha/pilha.c ./fila/fila.c
	./$(program)