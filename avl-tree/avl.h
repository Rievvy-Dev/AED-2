#ifndef AVL_H
#define AVL_H
#include <stdio.h>

typedef struct Node{
    int value;
    int balance;
    struct Node * rightNode;
    struct Node * leftNode;
} Node;

typedef Node * Tree;

Tree insertNode(Tree root, int value, int *growUp);

Tree deleteNode(Tree root, int value, int *decreased);

Tree singleLeftRotation(Tree root);

Tree singleRightRotation(Tree root);

Tree doubleLeftRotation(Tree root);

Tree doubleRightRotation(Tree root);

Tree rotation(Tree root);

Tree searchNode(Tree root, int value);

int highestValue(Tree root);

int amountPairs(Tree root);

void preOrder(Tree root);

void inOrder(Tree root);

void posOrder(Tree root);

void descending(Tree root);

#endif
