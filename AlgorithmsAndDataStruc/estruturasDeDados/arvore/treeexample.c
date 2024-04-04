#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
  int value;
  struct treenode *left;
  struct treenode *right;
} treenode;

treenode *createnode(int value){
  treenode* result = malloc(sizeof(treenode));
  if(result != NULL){
    result->left = NULL;
    result->right = NULL;
    result->value = value;
  }
}

void printtree(treenode *root){
  if(root == NULL){
    printf("----\n");
  } else {
    printf("%d\n", root->value);
    printtree(root->left);
    printtree(root->right);
  }
}

void cleartree(treenode *root) {
  if(root != NULL){
    cleartree(root->left);
    cleartree(root->right);
    free(root);
  }
}

bool findnumber(treenode *root, int value){
  if(root == NULL){
    return false;
  } if(root->value == value){
    return true;
  } if(value < root->value){
    return findnumber(root->left, value);
  } else{
    return findnumber(root->right, value);
  }
}

bool insertnumber(treenode **rootpr, int value){
  treenode *root = *rootpr;
  if(root == NULL){
    *rootpr = createnode(value);
    return true;
  } if(root->value == value){
    return false;
  } if(value < root->value){
    return insertnumber(&(root->left), value);
  } else{
    return insertnumber(&(root->right), value);
  }

}

int main() {
  treenode *root = createnode(1);
  root->left = createnode(2);
  root->right = createnode(3);
  root->left->left = createnode(4);
  root->left->right = createnode(5);
  root->right->left = createnode(6);
  root->right->right = createnode(7);
  printtree(root);

  printf("find 5: %d\n", findnumber(root, 5));

  return 0;
}