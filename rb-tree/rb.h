#ifndef RB_H
#define RB_H

enum color {RED, BLACK, DOUBLE_BLACK};

typedef struct Node {
    int value;
    enum color color;
    struct Node * leftNode;
    struct Node * rightNode;
    struct Node * father;
} Node;

typedef Node * Tree;

void initNode(Tree *root);

void insertNode(Tree *root, int value);

void deleteNode(Tree *root, int value);

void removeDoubleBlack(Tree *root, Tree doubleBlackNode);

void fixInsert (Tree *root, Tree node);

void fixDelete (Tree *root, Tree node);

void singleLeftRotation(Tree *root, Tree pivot);

void singleRightRotation(Tree *root, Tree pivot);

void doubleLeftRotation(Tree *root, Tree pivot);

void doubleRightRotation(Tree *root, Tree pivot);

void preOrder(Tree root);

void inOrder(Tree root);

void posOrder(Tree root);

void descending(Tree root);

void printElement(Tree root);

Tree brother(Tree root);

Tree uncle(Tree root);

Tree father(Tree root);

enum color nodeColor(Tree root);

int isRoot(Tree root);

int isLeftSon(Tree root);

int highestValue(Tree root);

#endif
