// Arquivo de Biblioteca de Funções.
// Este arquivo contém todas as funções mas não contém suas implementações.
// Além das funções este arquivo também contém as structs.

#ifndef BST_H
#define BST_H
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node *leftNode;
    struct Node *rightNode;
} Node;

typedef Node * Tree;

Tree insertNode(Tree root, int value);

Tree searchNode(Tree root, int value);

Tree deleteNode(Tree root, int value);

int highestValue(Tree root);

void preOrder(Tree root);

void inOrder(Tree root);

void posOrder(Tree root);

void descending(Tree root);

#endif
