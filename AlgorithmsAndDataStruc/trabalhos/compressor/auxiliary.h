#ifndef AUXILIARY_H
#define AUXILIARY_H


#include <stdio.h>

//Enzo Vasconcellos Pagotto - 13632844

typedef unsigned char byte;

void getByteFrequency(FILE* stream, unsigned int* bytesList);
int generateBit(FILE* stream, int position, byte* aux);

typedef struct TreeNode {
    int frequency;
    byte c;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createTreeNode(byte c, int frequency, TreeNode* left, TreeNode* right);

typedef struct ListNode {
    TreeNode* n;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
    int count;
} List;

ListNode* createListNode(TreeNode* treeNode);
void insertList(ListNode* node, List* list);
TreeNode* popMinList(List* list);

TreeNode* buildHuffmanTree(unsigned* bytesList);
void freeHuffmanTree(TreeNode* treeNode);


#endif 