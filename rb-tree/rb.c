#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

Tree nullNode;

void initNode (Tree *root) {
    *root = NULL;
    nullNode = (Tree)malloc(sizeof(struct Node));
    nullNode->color = DOUBLE_BLACK;
    nullNode->value = 0;
    nullNode->leftNode = NULL;
    nullNode->rightNode = NULL;
}

void insertNode (Tree *root, int value) {
    Tree father, position, new;
    
    position = *root;
    father = NULL;
    
    while (position != NULL) {
        father = position;
        
        if(value >= position->value) {
            position = position->rightNode;
        } else {
            position = position->leftNode;
        }
    }
    
    new = (Tree)malloc(sizeof(struct Node));
    
    new->value = value;
    new->leftNode = NULL;
    new->rightNode = NULL;
    new->father = father;
    new->color = RED;
    
    if (isRoot(new) == 1) {
        *root = new;
    } else {
        if (value >= father->value) {
            father->rightNode = new;
        } else {
            father->leftNode = new;
        }
    }
    
    fixInsert(root, new);
    
}

void fixInsert (Tree *root, Tree node) {
    while (nodeColor(node) == RED && nodeColor(node->father) == RED) {
        
        // Caso 1, Tio tem cor vermelha, então desce a cor do avô;
        if (nodeColor(uncle(node)) == RED) {
            
            uncle(node)->color = BLACK;
            node->father->color = BLACK;
            node->father->father->color = RED;
            node = node->father->father;
            
            continue;
        }
        
        // Caso 2, se o pai e o filho são esquerdos, rotação simples para a direita.
        if (isLeftSon(node) == 1 && isLeftSon(node->father) == 1) {
            singleRightRotation(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;
            
            continue;
        }
        
        // Caso 2b, se o pai e o filho são direitos, rotação simples para a esquerda.
        if (isLeftSon(node) == 0 && isLeftSon(node->father) == 0) {
            singleLeftRotation(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;
            
            continue;
        }
        
        // Caso 3, se o pai é esquerdo e o filho é direito, rotação dupla para direita.
        if (isLeftSon(node) == 0 && isLeftSon(node->father) == 1) {
            doubleRightRotation(root, node->father->father);
            node->color = BLACK;
            node->rightNode->color = RED;
            
            continue;
        }
        
        // Caso 3b, se o pai é direito e o filho é esquerdo, rotação dupla para esquerda.
        if (isLeftSon(node) == 1 && isLeftSon(node->father) == 0) {
            doubleLeftRotation(root, node->father->father);
            node->color = BLACK;
            node->leftNode->color = RED;
            
            continue;
        }
    } 
    (*root)->color = BLACK;
}

void deleteNode (Tree *root, int value) {
    Tree removableNode;
    removableNode = *root;
    
    while (removableNode != NULL) {
        if (removableNode->value == value) {
            if (removableNode->leftNode != NULL && removableNode->rightNode != NULL) {
                removableNode->value = highestValue(removableNode->leftNode);
                deleteNode(&removableNode->leftNode, removableNode->value);
                break;
            }
            if (removableNode->leftNode == NULL && removableNode->rightNode != NULL) {
                Tree assistant = removableNode->rightNode;
                removableNode->value = assistant->value;
                removableNode->rightNode = NULL;
                free(assistant);
                break;
            }
            if (removableNode->leftNode != NULL && removableNode->rightNode == NULL) {
                Tree assistant = removableNode->leftNode;
                removableNode->value = assistant->value;
                removableNode->leftNode = NULL;
                free(assistant);
                break;
            }
            if (removableNode->leftNode == NULL && removableNode->rightNode == NULL) {
                if (isRoot(removableNode) == 1) {
                    *root = NULL;
                    free(removableNode);
                    break;
                }
                if (removableNode->color == RED) {
                    if (isLeftSon(removableNode) == 1) {
                        removableNode->father->leftNode = NULL;
                    } else {
                        removableNode->father->rightNode = NULL;
                    }
                    free(removableNode);
                    break;
                } else {
                    nullNode->father = removableNode->father;
                    if (isLeftSon(removableNode) == 1) {
                        removableNode->father->leftNode = nullNode;
                    } else {
                        removableNode->father->rightNode = nullNode;
                    }
                    free(removableNode);
                    fixDelete(root, nullNode);
                    
                    break;
                }
            }
        } else {
            if (removableNode->value <= value) {
                removableNode = removableNode->rightNode;
            } else {
                removableNode = removableNode->leftNode;
            }
        }
    }
}

void fixDelete (Tree *root, Tree doubleBlackNode) {
    
    // Caso 1
    if (isRoot(doubleBlackNode) == 1) {
        
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
        
    }
    
    // Caso 2 
    if (nodeColor(doubleBlackNode->father) == BLACK && nodeColor(brother(doubleBlackNode)) == RED && nodeColor(brother(doubleBlackNode)->rightNode) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK) {
        
        if (isLeftSon(doubleBlackNode) == 1) {
            singleLeftRotation(root, doubleBlackNode->father);
        } else {
            singleRightRotation(root, doubleBlackNode->father);
        }
        doubleBlackNode->father->father->color = BLACK;
        doubleBlackNode->father->color = RED;
        
        fixDelete(root, doubleBlackNode);
        
        return;
        
    }
    
    // Caso 3
    if (nodeColor(doubleBlackNode->father) == BLACK && nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK) {
        
        Tree father = doubleBlackNode->father;
        
        brother(doubleBlackNode)->color = RED;
        father->color = DOUBLE_BLACK;
        
        removeDoubleBlack(root, doubleBlackNode);
        fixDelete(root, father);
        
        return;
        
    }
    
    // Caso 4
    if (nodeColor(doubleBlackNode->father) == RED && nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK) {
        
        doubleBlackNode->father->color = BLACK;
        brother(doubleBlackNode)->color = RED;
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 5a
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == RED && isLeftSon(brother(doubleBlackNode)) == 0) {
        
        singleRightRotation(root, brother(doubleBlackNode));
        brother(doubleBlackNode)->color = BLACK;
        brother(doubleBlackNode)->rightNode->color = RED;
        
        fixDelete(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 5b
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == RED && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK && isLeftSon(brother(doubleBlackNode)) == 1) {
        
        singleLeftRotation(root, brother(doubleBlackNode));
        brother(doubleBlackNode)->color = BLACK;
        brother(doubleBlackNode)->leftNode->color = RED;
        
        fixDelete(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 6a
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == RED && isLeftSon(brother(doubleBlackNode)) == 1) {
        
        singleRightRotation(root, doubleBlackNode->father);
        enum color assistantColor = doubleBlackNode->father->father->color;
        doubleBlackNode->father->father->color = doubleBlackNode->father->color;
        doubleBlackNode->father->color = assistantColor;
        uncle(doubleBlackNode)->color = BLACK;
        
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 6b
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == RED && isLeftSon(brother(doubleBlackNode)) == 0) {
        
        singleLeftRotation(root, doubleBlackNode->father);
        enum color assistantColor = doubleBlackNode->father->father->color;
        doubleBlackNode->father->father->color = doubleBlackNode->father->color;
        doubleBlackNode->father->color = assistantColor;
        uncle(doubleBlackNode)->color = BLACK;
        
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
    }
}

void removeDoubleBlack (Tree *root, Tree doubleBlackNode) {
    if (doubleBlackNode == nullNode) {
        if (isRoot(doubleBlackNode) == 1) {
            *root = NULL;
        } else {
            if (isLeftSon(doubleBlackNode) == 1) {
                doubleBlackNode->father->leftNode = NULL;
            } else {
                doubleBlackNode->father->rightNode = NULL;
            }
        }
    }
}

void singleLeftRotation (Tree *root, Tree pivot) {
    Tree u, t2;
    
    u = pivot->rightNode;
    t2 = u->leftNode;
    
    int pivotIsLeftSon = isLeftSon(pivot);
    
    pivot->rightNode = t2;
    
    if (t2 != NULL) {
        t2->father = pivot;
    }
    
    u->leftNode = pivot;
    u->father = pivot->father;
    pivot->father = u;
    
    if (isRoot(u)) {
        *root = u;
    } else {
        if (pivotIsLeftSon == 1) {
            u->father->leftNode = u;
        } else {
            u->father->rightNode = u;
        }
    }
    
}

void singleRightRotation (Tree *root, Tree pivot) {
    Tree u, t1;

    u = pivot->leftNode;
    t1 = u->rightNode;
    
    int pivotIsLeftSon = isLeftSon(pivot);
    
    pivot->leftNode = t1;
    
    if (t1 != NULL) {
        t1->father = pivot;
    }
    
    u->rightNode = pivot;
    u->father = pivot->father;
    pivot->father = u;
    
    if (isRoot(u)) {
        *root = u;
    } else {
        if (pivotIsLeftSon == 1) {
            u->father->leftNode = u;
        } else {
            u->father->rightNode = u;
        }
    }
}

void doubleLeftRotation (Tree *root, Tree pivot) {
    Tree u = pivot->rightNode;
    
    singleRightRotation(root, u);
    singleLeftRotation(root, pivot);
}

void doubleRightRotation (Tree *root, Tree pivot) {
    Tree u = pivot->leftNode;
    
    singleLeftRotation(root, u);
    singleRightRotation(root, pivot);
}

int isRoot (Tree root) {
    if (root->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isLeftSon (Tree root) {
    if (root->father != NULL && root == root->father->leftNode) {
        return 1;
    } else {
        return 0;
    }
}

enum color nodeColor (Tree root) {
    enum color color;
    
    if (root == NULL) {
        color = BLACK;
    } else {
        color = root->color;
    }
    
    return color;
}

Tree brother (Tree root) {
    if (isLeftSon(root) == 1) {
        return root->father->rightNode;
    } else {
        return root->father->leftNode;
    }
}

Tree uncle (Tree root) {
    return brother(root->father);
}

void printElement (Tree root) {
    switch (root->color) {
        case BLACK:
            printf("\x1b[30m[%d]\x1b[0m", root->value);
            break;
        case RED:
            printf("\x1b[31m[%d]\x1b[0m", root->value);
            break;
        case DOUBLE_BLACK:
            printf("\x1b[32m[%d]\x1b[0m", root->value);
            break;
    }
}

int highestValue (Tree root) {
    if (root->leftNode == NULL && root->rightNode == NULL) {
        return root->value;
    } else {
        if (root->rightNode != NULL) {
            return highestValue(root->rightNode);
        } else {
            return root->value;
        }
    }
}

void preOrder (Tree root) {
    if (root != NULL) {
        printElement(root);
        preOrder(root->leftNode);
        preOrder(root->rightNode);
    }
}















