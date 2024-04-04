CC = gcc
compressorProgram = compressor
decompressorProgram = decompressor

clean:
	rm -r */*.o $(program)

compile-compressor: ./compressor.c ./auxiliary.c ./auxiliary.h
	$(CC) -o $(compressorProgram) ./compressor.c ./auxiliary.c

compile-decompressor: ./decompressor.c ./auxiliary.c ./auxiliary.h
	$(CC) -o $(decompressorProgram) ./decompressor.c ./auxiliary.c


execute-compressor:
	$(CC) -o $(compressorProgram) ./compressor.c ./auxiliary.c
	./$(compressorProgram) ./main.c

execute-decompressor:
	$(CC) -o $(decompressorProgram) ./decompressor.c ./auxiliary.c
	./$(decompressorProgram)  ./main.comp