CC = gcc
compactor-program = compressor
decompressor-program = decompressor

clean:
	rm -r src/*/*.o $(program)

compile-compactor: ./huffman.c  ./huffman.h
	$(CC) -o $(compactor-program) ./huffman.c

compile-decompressor: ./src/decompressor.c ./src/byte/byte.c ./src/byte/byte.h ./src/huffman/huffman.c ./src/huffman/huffman.h ./src/list/list.c ./src/list/list.h ./src/tree/tree.c ./src/tree/tree.h
	$(CC) -o $(decompressor-program) ./src/decompressor.c ./src/byte/byte.c ./src/huffman/huffman.c ./src/list/list.c ./src/tree/tree.c


exec-compactor:
	$(CC) -o $(compactor-program) ./src/compressor.c ./src/byte/byte.c ./src/huffman/huffman.c ./src/list/list.c ./src/tree/tree.c
	./$(compactor-program) ./src/main.c

exec-decompressor:
	$(CC) -o $(decompressor-program) ./src/decompressor.c ./src/byte/byte.c ./src/huffman/huffman.c ./src/list/list.c ./src/tree/tree.c
	./$(decompressor-program)  ./main.comp