CC = gcc
program = main

all: main.c ./skipList/skipList.c ./skipList/skipList.h
	$(CC) -o $(program) main.c ./skipList/skipList.c

clean:
	rm -r */*.o $(program)

run:
	$(CC) -o $(program) main.c ./skipList/skipList.c
	./$(program)