#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 256
#define MAX_CODE_LENGTH 256

typedef struct Node {
    char data;
    int frequency;
    struct Node *left, *right;
} Node;

typedef struct MinHeap {
    int size;
    int capacity;
    Node **array;
} MinHeap;

typedef struct HuffmanCode {
    char data;
    char code[MAX_CODE_LENGTH];
} HuffmanCode;

Node* createNode(char data, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*));
    return minHeap;
}

void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swapNode(&minHeap->array[index], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

MinHeap* buildHuffmanTree(char data[], int frequency[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], frequency[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    while (minHeap->size > 1) {
        Node* left = minHeap->array[0];
        minHeap->array[0] = minHeap->array[--minHeap->size];

        minHeapify(minHeap, 0);

        Node* right = minHeap->array[0];

        Node* mergeNode = createNode('$', left->frequency + right->frequency);
        mergeNode->left = left;
        mergeNode->right = right;

        minHeap->array[0] = mergeNode;
        minHeapify(minHeap, 0);
    }

    return minHeap;
}

void generateHuffmanCodes(Node* root, char code[], int top, HuffmanCode huffmanCodes[]) {
    if (root->left) {
        code[top] = '0';
        generateHuffmanCodes(root->left, code, top + 1, huffmanCodes);
    }

    if (root->right) {
        code[top] = '1';
        generateHuffmanCodes(root->right, code, top + 1, huffmanCodes);
    }

    if (!root->left && !root->right) {
        huffmanCodes[root->data].data = root->data;
        strncpy(huffmanCodes[root->data].code, code, top);
        huffmanCodes[root->data].code[top] = '\0';
    }
}

void writeHuffmanCodesToFile(FILE* file, HuffmanCode huffmanCodes[]) {
    for (int i = 0; i < MAX_TREE_NODES; ++i) {
        if (huffmanCodes[i].data != '\0') {
            fprintf(file, "%c%s\n", huffmanCodes[i].data, huffmanCodes[i].code);
        }
    }
}

void compressFile(FILE* inputFile, FILE* compressedFile, HuffmanCode huffmanCodes[]) {
    char buffer[MAX_CODE_LENGTH] = "";
    char c;

    fseek(inputFile, 0, SEEK_SET);

    while ((c = fgetc(inputFile)) != EOF) {
        strcat(buffer, huffmanCodes[c].code);

        while (strlen(buffer) >= 8) {
            char byte = 0;
            for (int i = 0; i < 8; ++i) {
                byte = (byte << 1) | (buffer[i] - '0');
            }

            fputc(byte, compressedFile);
            memmove(buffer, buffer + 8, strlen(buffer) - 8 + 1);
        }
    }

    int remainingBits = strlen(buffer);
    if (remainingBits > 0) {
        char byte = 0;
        for (int i = 0; i < remainingBits; ++i) {
            byte = (byte << 1) | (buffer[i] - '0');
        }

        byte <<= (8 - remainingBits);
        fputc(byte, compressedFile);
    }
}

void decompressFile(FILE *compressedFile, FILE *decompressedFile, Node *root) {
    Node *currentNode = root;
    int bit;

    while ((bit = fgetc(compressedFile)) != EOF) {
        for (int i = 7; i >= 0; --i) {
            int currentBit = (bit >> i) & 1;

            if (currentBit == 0) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }

            if (!currentNode->left && !currentNode->right) {
                fputc(currentNode->data, decompressedFile);
                currentNode = root;
            }
        }
    }
}

int main() {
    char data[MAX_TREE_NODES];
    int frequency[MAX_TREE_NODES] = {0};
    int size = 0;

    FILE* inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    // Count the frequency of each character in the input file
    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (frequency[c] == 0) {
            data[size++] = c;
        }
        frequency[c]++;
    }

    fclose(inputFile);

    // Build the Huffman tree
    MinHeap* minHeap = buildHuffmanTree(data, frequency, size);
    Node* root = minHeap->array[0];

    // Generate Huffman codes
    HuffmanCode huffmanCodes[MAX_TREE_NODES] = {{'\0', ""}};
    char code[MAX_CODE_LENGTH] = "";
    generateHuffmanCodes(root, code, 0, huffmanCodes);

    // Write Huffman codes to a file
    FILE* codeFile = fopen("codes.comp", "w");
    if (!codeFile) {
        fprintf(stderr, "Error opening code file.\n");
        return 1;
    }
    writeHuffmanCodesToFile(codeFile, huffmanCodes);
    fclose(codeFile);

    // Compress the input file
    FILE *compressedFile = fopen("output.comp", "wb");
    if (!compressedFile) {
        fprintf(stderr, "Error opening compressed file.\n");
        return 1;
    }
    if (!inputFile) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }
    compressFile(inputFile, compressedFile, huffmanCodes);
    fclose(inputFile);
    fclose(compressedFile);

    // Decompress the compressed file
    compressedFile = fopen("output.comp", "rb");  // Open the compressed file for reading in binary mode
    if (!compressedFile) {
        fprintf(stderr, "Error opening compressed file.\n");
        return 1;
    }

    FILE *decompressedFile = fopen("output_decomp.txt", "w");
    if (!decompressedFile) {
        fprintf(stderr, "Error opening decompressed file.\n");
        return 1;
    }

    // Decompress the file
    decompressFile(compressedFile, decompressedFile, root);

    fclose(compressedFile);
    fclose(decompressedFile);

    printf("Compression and Decompression done!\n");

    return 0;
}
