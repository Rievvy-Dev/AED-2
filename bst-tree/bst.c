// Este arquivo contém todas as implementações das funções do arquivo de biblioteca.

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

Tree insertNode (Tree root, int value) {
    if (root == NULL) {
        Tree node = (Tree)malloc(sizeof(root));
        
        node->value = value;
        node->rightNode = NULL;
        node->leftNode = NULL;
        
        return node;
    } else {
        if (root->value < value) {
            root->rightNode = insertNode(root->rightNode, value);
        } else {
            root->leftNode = insertNode(root->leftNode, value);
        }
        return root;
    }
}

Tree searchNode (Tree root, int value) {
    if (root->value == value) {
        return root;
    } else {
        if (root->value < value) {
            root->rightNode = searchNode(root->rightNode, value);
        } else {
            root->leftNode = searchNode(root->leftNode, value);
        }
        return root;
    }
}

int highestValue (Tree root) {
    int highest;
    
    if (root->rightNode == NULL) {
        return root->value;
    } else {
        if (root->rightNode != NULL) {
           highest = highestValue(root->rightNode); 
        } else {
            return root->value;
        }
    }
}

Tree deleteNode (Tree root, int value) {
    if (root != NULL) {
        if (root->value == value) {
            if (root->rightNode == NULL && root->leftNode == NULL) {
                free(root);
                return NULL;
            } else if (root->rightNode != NULL && root->leftNode == NULL) {
                Tree assistant = root->rightNode;
                free(root);
                return assistant;
            } else if (root->rightNode == NULL && root->leftNode != NULL) {
                Tree assistant = root->leftNode;
                free(root);
                return assistant;
            } else {
                root->value = highestValue(root->leftNode);
                root->leftNode = deleteNode(root->leftNode, root->value);
                return root;
            }
        } else {
            if (root->value < value) {
                root->rightNode = deleteNode(root->rightNode, value);
            } else {
                root->leftNode = deleteNode(root->leftNode, value);
            }
            return root;
        }
    }
    return NULL;
}

void preOrder (Tree root) {
    if (root != NULL) {
        printf("[%d]", root->value);
        preOrder(root->leftNode);
        preOrder(root->rightNode);
    }
}

void inOrder (Tree root) {
    if (root != NULL) {
        inOrder(root->leftNode);
        printf("[%d]", root->value);
        inOrder(root->rightNode);
    }
}

void posOrder (Tree root) {
    if (root != NULL) {
        posOrder(root->leftNode);
        posOrder(root->rightNode);
        printf("[%d]", root->value);
    }
}

void descending (Tree root) {
    if (root != NULL) {
        descending(root->rightNode);
        printf("[%d]", root->value);
        descending(root->leftNode);
    }
}







