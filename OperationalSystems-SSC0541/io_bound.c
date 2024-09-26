#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char buffer[100];
    int i;

    file = fopen("io_bound_test.txt", "w+");
    if (file == NULL) {
        perror("Erro ao criar arquivo");
        exit(1);
    }

    for (i = 0; i < 10000; i++) {
        fprintf(file, "Linha de teste %d\n", i);
    }

    while (1) {
        fseek(file, 0, SEEK_SET);

        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            fprintf(file, "%s", buffer);
            fflush(file); // Força a escrita imediata
        }

        usleep(1000);  
    }

    fclose(file);

    return 0;
}
