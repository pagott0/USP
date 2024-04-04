#include <stdlib.h>

#include "auxiliary.h"

//Enzo Vasconcellos Pagotto - 13632844

void getByteFrequency(FILE* stream, unsigned int* bytesList) {
    byte c;

    while (fread(&c, 1, 1, stream) >= 1) {
        bytesList[(byte)c]++;
    }

    rewind(stream);
}

int generateBit(FILE* stream, int position, byte* aux) {
    if (position % 8 == 0) {
        fread(aux, 1, 1, stream);
    }

    return !!(*aux & 1 << position % 8);
}

TreeNode* createTreeNode(byte c, int frequency, TreeNode* left, TreeNode* right) {
    TreeNode* novo = (TreeNode*) malloc(sizeof(TreeNode));
    if (novo == NULL) return NULL;

    novo->c = c;
    novo->frequency = frequency;
    novo->left = left;
    novo->right = right;

    return novo;
}

ListNode* createListNode(TreeNode* treeNode) {
    ListNode* novo = (ListNode*) malloc(sizeof(ListNode));
    if (novo == NULL) return NULL;

    novo->n = treeNode;
    novo->next = NULL;

    return novo;
}

void insertList(ListNode* node, List* list) {
    if (!list->head) {
        list->head = node;
    } else if (node->n->frequency < list->head->n->frequency) {
        node->next = list->head;
        list->head = node;
    } else {
        ListNode* aux = list->head->next;
        ListNode* aux2 = list->head;

        while (aux && aux->n->frequency <= node->n->frequency) {
            aux2 = aux;
            aux = aux2->next;
        }

        aux2->next = node;
        node->next = aux;
    }

    list->count++;
}

TreeNode* popMinList(List* list) {
    ListNode* aux = list->head;
    TreeNode* aux2 = aux->n;

    list->head = aux->next;

    free(aux);
    aux = NULL;

    list->count--;

    return aux2;
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

        TreeNode* soma = createTreeNode('#',leftNode->frequency + rightNode->frequency, leftNode, rightNode);
        insertList(createListNode(soma), &list);
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