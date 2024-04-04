#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./auxiliary.h"

//Enzo Vasconcellos Pagotto - 13632844

// Function prototypes
char* generateCompressedFilename(char* inputFilePath);
int getHuffmanCode(TreeNode* node, byte targetByte, char* buffer, int bufferSize);
void handleFileNotFoundError();
void removeFirstLineFromFile(char* filePath);
void compressUsingHuffman(char* inputFilePath);

int main(int _, char *argv[]) {
    compressUsingHuffman(argv[1]);
    return 0;
}

// Function to get the output filename with a different approach
char* generateCompressedFilename(char* inputFilePath) {
    char* lastSlash = strrchr(inputFilePath, '/');
    char* filenameStart = lastSlash ? lastSlash + 1 : inputFilePath;
    char* lastDot = strrchr(filenameStart, '.');

    if (lastDot) {
        size_t filenameLength = lastDot - filenameStart;
        char* filename = malloc(filenameLength + 1);

        strncpy(filename, filenameStart, filenameLength);
        filename[filenameLength] = '\0';
        strcat(filename, ".comp");

        return filename;
    } else {
        char* filename = malloc(strlen(filenameStart) + 6);
        strcpy(filename, filenameStart);
        strcat(filename, ".comp");

        return filename;
    }
}

// Function to get the Huffman code for a specific byte
int getHuffmanCode(TreeNode* node, byte targetByte, char* buffer, int bufferSize) {
    if (!(node->left || node->right) && node->c == targetByte) {
        buffer[bufferSize] = '\0';
        return 1;
    }

    int found = 0;

    if (node->left) {
        buffer[bufferSize] = '0';
        found = getHuffmanCode(node->left, targetByte, buffer, bufferSize + 1);
    }

    if (!found && node->right) {
        buffer[bufferSize] = '1';
        found = getHuffmanCode(node->right, targetByte, buffer, bufferSize + 1);
    }

    if (!found) {
        buffer[bufferSize] = '\0';
    }

    return found;
}

// Function to handle errors when a file is not found
void handleFileNotFoundError() {
    printf("Unable to find the file\n");
    exit(0);
}

// Function to remove the first line from a file
void removeFirstLineFromFile(char* filePath) {
    char tempFilename[FILENAME_MAX];
    tmpnam(tempFilename);

    FILE* inputFile = fopen(filePath, "r");

    if (inputFile != NULL) {
        FILE* tempFile = fopen(tempFilename, "w");

        if (tempFile != NULL) {
            int character;
            while ((character = fgetc(inputFile)) != EOF && character != '\n') {  }

            while ((character = fgetc(inputFile)) != EOF) {
                fputc(character, tempFile);
            }

            fclose(inputFile);
            fclose(tempFile);

            remove(filePath);
            rename(tempFilename, filePath);

            printf("First line removed successfully.\n");
        } else {
            printf("Error opening the temporary file.\n");
            fclose(inputFile);
        }
    } else {
        printf("Error opening the original file.\n");
    }
}

// Function to compress a file using Huffman coding
void compressUsingHuffman(char* inputFilePath) {
    clock_t startTime, endTime;
    startTime = clock();

    char* compressedFilename = generateCompressedFilename(inputFilePath);

    unsigned frequencyList[256] = {0};

    FILE* inputFile = fopen(inputFilePath, "rb");
    FILE* compressedFile = fopen(compressedFilename, "wb");

    if (!inputFile || !compressedFile) {
        handleFileNotFoundError();
    }

    getByteFrequency(inputFile, frequencyList);

    TreeNode* huffmanTreeRoot = buildHuffmanTree(frequencyList);

    fwrite(frequencyList, 256, sizeof(frequencyList[0]), compressedFile);

    fseek(compressedFile, sizeof(unsigned int), SEEK_CUR);

    byte currentByte;
    unsigned bitSize = 0;
    byte buffer = 0;

    while (fread(&currentByte, 1, 1, inputFile) >= 1) {
        char huffmanCodeBuffer[1024] = {0};

        getHuffmanCode(huffmanTreeRoot, currentByte, huffmanCodeBuffer, 0);

        for (char* i = huffmanCodeBuffer; *i; i++) {
            if (*i == '1') {
                buffer |= (1 << (bitSize % 8));
            }

            bitSize++;

            if (bitSize % 8 == 0) {
                fwrite(&buffer, 1, 1, compressedFile);
                buffer = 0;
            }
        }
    }

    fwrite(&buffer, 1, 1, compressedFile);

    fseek(compressedFile, 256 * sizeof(unsigned int), SEEK_SET);

    fwrite(&bitSize, 1, sizeof(unsigned), compressedFile);

    endTime = clock();
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    fseek(inputFile, 0L, SEEK_END);
    double inputSize = ftell(inputFile);

    fseek(compressedFile, 0L, SEEK_END);
    double compressedSize = ftell(compressedFile);

    freeHuffmanTree(huffmanTreeRoot);

    printf("Input File: %s (%g bytes)\nCompressed File: %s (%g bytes)\nTime spent: %gs\n", inputFilePath, inputSize / 1000, compressedFilename, compressedSize / 1000, elapsedTime);
    printf("Compression Percentage: %d%%\n", (int) ((100 * compressedSize) / inputSize));

    fclose(inputFile);
    fclose(compressedFile);

    removeFirstLineFromFile(inputFilePath);
}
