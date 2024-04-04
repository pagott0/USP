#include <string.h>
#include <stdio.h>

//Enzo Vasconcellos Pagotto - 13632844

typedef unsigned char byte;

// Data structures
typedef struct TreeNode {
    int frequency;
    byte data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ListNode {
    TreeNode* node;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
    int count;
} List;

// Function prototypes
ListNode* createListNode(TreeNode* treeNode);
TreeNode* createTreeNode(byte data, int frequency, TreeNode* left, TreeNode* right);
void insertList(ListNode* node, List* list);
TreeNode* popMinList(List* list);
void getByteFrequency(FILE* stream, unsigned int* bytesList);
int getCode(TreeNode* node, byte data, char* buffer, int size);
TreeNode* buildHuffmanTree(unsigned* bytesList);
void freeHuffmanTree(TreeNode* treeNode);
int generateBit(FILE* stream, int position, byte* aux);
void fileError();
void compressFile(const char* inputFilename, const char* outputFilename);
void decompressFile(const char* inputFilename, const char* outputFilename);
void instructions();

int main(int argc, char *argv[]) {
    if (argc < 4 && strcmp("-h", argv[1]) != 0 && strcmp("--help", argv[1]) != 0) {
        printf("Error: Improper use of the program.\n\n");

        instructions();

        return 0;
    }

    if (strcmp("-c", argv[1]) == 0) {
        if (strstr(argv[3], ".pd")) {
            compressFile(argv[2], argv[3]);
        } else {
            printf("The compressed file must have the extension '.pd'.\n");
            printf("Example: \n\t./main -c compress.this this.pd\n");

            return 0;
        }
    } else if (strcmp("-x", argv[1]) == 0) {
        if (strstr(argv[2], ".pd")) {
            decompressFile(argv[2], argv[3]);
        } else {
            printf("The file to be decompressed must have the extension '.pd'.\n");
            printf("Example: \n\t./main -x decompress.pd this.extension\n");

            return 0;
        }
    } else if (strcmp("-h", argv[1]) == 0 || strcmp("--help", argv[1]) == 0) {
        instructions();
        return 0;
    } else {
        instructions();
        return 0;
    }

    return 0;
}

ListNode* createListNode(TreeNode* treeNode) {
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    if (newNode == NULL) return NULL;

    newNode->node = treeNode;
    newNode->next = NULL;

    return newNode;
}

TreeNode* createTreeNode(byte data, int frequency, TreeNode* left, TreeNode* right) {
    TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
    if (newNode == NULL) return NULL;

    newNode->data = data;
    newNode->frequency = frequency;
    newNode->left = left;
    newNode->right = right;

    return newNode;
}

void insertList(ListNode* node, List* list) {
    if (!list->head) {
        list->head = node;
    } else if (node->node->frequency < list->head->node->frequency) {
        node->next = list->head;
        list->head = node;
    } else {
        ListNode* temp = list->head->next;
        ListNode* temp2 = list->head;

        while (temp && temp->node->frequency <= node->node->frequency) {
            temp2 = temp;
            temp = temp2->next;
        }

        temp2->next = node;
        node->next = temp;
    }

    list->count++;
}

TreeNode* popMinList(List* list) {
    ListNode* temp = list->head;
    TreeNode* temp2 = temp->node;

    list->head = temp->next;

    free(temp);
    temp = NULL;

    list->count--;

    return temp2;
}

void getByteFrequency(FILE* stream, unsigned int* bytesList) {
    byte c;

    while (fread(&c, 1, 1, stream) >= 1) {
        bytesList[(byte)c]++;
    }

    rewind(stream);
}

int getCode(TreeNode* node, byte data, char* buffer, int size) {
    if (!(node->left || node->right) && node->data == data) {
        buffer[size] = '\0';
        return 1;
    }

    int found = 0;

    if (node->left) {
        buffer[size] = '0';
        found = getCode(node->left, data, buffer, size + 1);
    }

    if (!found && node->right) {
        buffer[size] = '1';
        found = getCode(node->right, data, buffer, size + 1);
    }

    if (!found) {
        buffer[size] = '\0';
    }

    return found;
}

TreeNode* buildHuffmanTree(unsigned* bytesList) {
    List list = {NULL, 0};

    for (int i = 0; i < 256; i++) {
        if (bytesList[i]) {
            insertList(createListNode(createTreeNode(i, bytesList[i], NULL, NULL)), &list);
        }
    }

    while (list.count > 1) {
        TreeNode* leftNode = popMinList(&list);
        TreeNode* rightNode = popMinList(&list);

        TreeNode* sumNode = createTreeNode('#', leftNode->frequency + rightNode->frequency, leftNode, rightNode);
        insertList(createListNode(sumNode), &list);
    }

    return popMinList(&list);
}

void freeHuffmanTree(TreeNode* treeNode) {
    if (!treeNode) return;

    TreeNode* left = treeNode->left;
    TreeNode* right = treeNode->right;

    free(treeNode);
    freeHuffmanTree(left);
    freeHuffmanTree(right);
}

int generateBit(FILE* stream, int position, byte* aux) {
    if (position % 8 == 0) {
        fread(aux, 1, 1, stream);
    }

    return !!(*aux & 1 << position % 8);
}

void fileError() {
    printf("File not found\n");
    exit(0);
}

void compressFile(const char* inputFilename, const char* outputFilename) {
    clock_t start, finish;
    start = clock();

    unsigned bytesList[256] = {0};

    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        fileError();
    }

    getByteFrequency(inputFile, bytesList);

    TreeNode* root = buildHuffmanTree(bytesList);

    fwrite(bytesList, 256, sizeof(bytesList[0]), outputFile);

    fseek(outputFile, sizeof(unsigned int), SEEK_CUR);

    byte data;
    unsigned size = 0;
    byte aux = 0;

    while (fread(&data, 1, 1, inputFile) >= 1) {
        char buffer[1024] = {0};

        getCode(root, data, buffer, 0);

        for (char* i = buffer; *i; i++) {
            if (*i == '1') {
                aux = aux | (1 << (size % 8));
            }

            size++;

            if (size % 8 == 0) {
                fwrite(&aux, 1, 1, outputFile);
                aux = 0;
            }
        }
    }

    fwrite(&aux, 1, 1, outputFile);

    fseek(outputFile, 256 * sizeof(unsigned int), SEEK_SET);

    fwrite(&size, 1, sizeof(unsigned), outputFile);

    finish = clock();
    double spentTime = (double)(finish - start) / CLOCKS_PER_SEC;

    fseek(inputFile, 0L, SEEK_END);
    double inputFileSize = ftell(inputFile);

    fseek(outputFile, 0L, SEEK_END);
    double outputFileSize = ftell(outputFile);

    freeHuffmanTree(root);

    printf("Input File: %s (%g bytes)\nOutput File: %s (%g bytes)\nTime Spent: %gs\n", inputFilename, inputFileSize / 1000, outputFilename, outputFileSize / 1000, spentTime);
    printf("Compression Ratio: %d%%\n", (int) ((100 * outputFileSize) / inputFileSize));

    fclose(inputFile);
    fclose(outputFile);
}

void decompressFile(const char* inputFilename, const char* outputFilename) {
    clock_t start, finish;
    start = clock();

    unsigned bytesList[256] = {0};

    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        fileError();
    }

    fread(bytesList, 256, sizeof(bytesList[0]), inputFile);

    TreeNode* root = buildHuffmanTree(bytesList);

    unsigned size;
    fread(&size, 1, sizeof(size), inputFile);

    unsigned pos = 0;
    byte aux = 0;

    while (pos < size) {
        TreeNode* currentNode = root;

        while (currentNode->left || currentNode->right) {
            currentNode = generateBit(inputFile, pos++, &aux) ? currentNode->right : currentNode->left;
        }

        fwrite(&(currentNode->data), 1, 1, outputFile);
    }

    freeHuffmanTree(root);

    finish = clock();
    double spentTime = (double)(finish - start) / CLOCKS_PER_SEC;

    fseek(inputFile, 0L, SEEK_END);
    double inputFileSize = ftell(inputFile);

    fseek(outputFile, 0L, SEEK_END);
    double outputFileSize = ftell(outputFile);

    printf("Input File: %s (%g bytes)\nOutput File: %s (%g bytes)\nTime Spent: %gs\n", inputFilename, inputFileSize / 1000, outputFilename, outputFileSize / 1000, spentTime);
    printf("Decompression Ratio: %d%%\n", (int)((100 * outputFileSize) / inputFileSize));

    fclose(inputFile);
    fclose(outputFile);
}

void instructions() {
    printf("Usage: main [OPTION] [FILE] [FILE]\n\n");
    printf("Options:\n");
    printf("\t-c\t\tCompress\n");
    printf("\tExample: \t./main -c compress.this this.pd\n");
    printf("\n\t-x\t\tDecompress\n");
    printf("\tExample: \t./main -x decompress-this.pd this.extension\n");
    printf("\n\t-h, --help\tHelp Information\n");
}
