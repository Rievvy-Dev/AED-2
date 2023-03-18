#include <stdio.h>
#include <stdlib.h>
#include "index.h"


RbNode nullNode;

void initRbTree (RbNode *root) {
    *root = NULL;
    nullNode = (RbNode)malloc(sizeof(struct rbNode));
    nullNode->color = DOUBLE_BLACK;
    nullNode->data = NULL;
    nullNode->leftNode = NULL;
    nullNode->rightNode = NULL;
}

void insertNodeRB (RbNode *root, AbstractData data) {
    RbNode father, position, new;
    
    position = *root;
    father = NULL;
    
    while (position != NULL) {
        father = position;
        
        if(data->keyRB >= position->data->keyRB) {
            position = position->rightNode;
        } else {
            position = position->leftNode;
        }
    }
    
    new = (RbNode)malloc(sizeof(struct rbNode));
    
    new->data = data;
    new->leftNode = NULL;
    new->rightNode = NULL;
    new->father = father;
    new->color = RED;
    
    if (isRoot(new) == 1) {
        *root = new;
    } else {
        if (data->keyRB >= father->data->keyRB) {
            father->rightNode = new;
        } else {
            father->leftNode = new;
        }
    }
    
    fixInsert(root, new);
    
}

void fixInsert (RbNode *root, RbNode node) {
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
            singleRightRotationRB(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;
            
            continue;
        }
        
        // Caso 2b, se o pai e o filho são direitos, rotação simples para a esquerda.
        if (isLeftSon(node) == 0 && isLeftSon(node->father) == 0) {
            singleLeftRotationRB(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;
            
            continue;
        }
        
        // Caso 3, se o pai é esquerdo e o filho é direito, rotação dupla para direita.
        if (isLeftSon(node) == 0 && isLeftSon(node->father) == 1) {
            doubleRightRotationRB(root, node->father->father);
            node->color = BLACK;
            node->rightNode->color = RED;
            
            continue;
        }
        
        // Caso 3b, se o pai é direito e o filho é esquerdo, rotação dupla para esquerda.
        if (isLeftSon(node) == 1 && isLeftSon(node->father) == 0) {
            doubleLeftRotationRB(root, node->father->father);
            node->color = BLACK;
            node->leftNode->color = RED;
            
            continue;
        }
    } 
    (*root)->color = BLACK;
}

void deleteNodeRB (RbNode *root, int value) {
    RbNode removableNode;
    removableNode = *root;
    
    while (removableNode != NULL) {
        if (removableNode->data->keyRB == value) {
            if (removableNode->leftNode != NULL && removableNode->rightNode != NULL) {
                removableNode->data = highestValueRB(removableNode->leftNode);
                deleteNodeRB(&removableNode->leftNode, removableNode->data->keyRB);
                break;
            }
            if (removableNode->leftNode == NULL && removableNode->rightNode != NULL) {
                RbNode assistant = removableNode->rightNode;
                removableNode->data = assistant->data;
                removableNode->rightNode = NULL;
                free(assistant);
                break;
            }
            if (removableNode->leftNode != NULL && removableNode->rightNode == NULL) {
                RbNode assistant = removableNode->leftNode;
                removableNode->data = assistant->data;
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
            if (removableNode->data->keyRB <= value) {
                removableNode = removableNode->rightNode;
            } else {
                removableNode = removableNode->leftNode;
            }
        }
    }
}

void fixDelete (RbNode *root, RbNode doubleBlackNode) {
    
    // Caso 1
    if (isRoot(doubleBlackNode) == 1) {
        
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
        
    }
    
    // Caso 2 
    if (nodeColor(doubleBlackNode->father) == BLACK && nodeColor(brother(doubleBlackNode)) == RED && nodeColor(brother(doubleBlackNode)->rightNode) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK) {
        
        if (isLeftSon(doubleBlackNode) == 1) {
            singleLeftRotationRB(root, doubleBlackNode->father);
        } else {
            singleRightRotationRB(root, doubleBlackNode->father);
        }
        doubleBlackNode->father->father->color = BLACK;
        doubleBlackNode->father->color = RED;
        
        fixDelete(root, doubleBlackNode);
        
        return;
        
    }
    
    // Caso 3
    if (nodeColor(doubleBlackNode->father) == BLACK && nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK) {
        
        RbNode father = doubleBlackNode->father;
        
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
        
        singleRightRotationRB(root, brother(doubleBlackNode));
        brother(doubleBlackNode)->color = BLACK;
        brother(doubleBlackNode)->rightNode->color = RED;
        
        fixDelete(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 5b
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == RED && nodeColor(brother(doubleBlackNode)->leftNode) == BLACK && isLeftSon(brother(doubleBlackNode)) == 1) {
        
        singleLeftRotationRB(root, brother(doubleBlackNode));
        brother(doubleBlackNode)->color = BLACK;
        brother(doubleBlackNode)->leftNode->color = RED;
        
        fixDelete(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 6a
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->leftNode) == RED && isLeftSon(brother(doubleBlackNode)) == 1) {
        
        singleRightRotationRB(root, doubleBlackNode->father);
        enum color assistantColor = doubleBlackNode->father->father->color;
        doubleBlackNode->father->father->color = doubleBlackNode->father->color;
        doubleBlackNode->father->color = assistantColor;
        uncle(doubleBlackNode)->color = BLACK;
        
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
    }
    
    // Caso 6b
    if (nodeColor(brother(doubleBlackNode)) == BLACK && nodeColor(brother(doubleBlackNode)->rightNode) == RED && isLeftSon(brother(doubleBlackNode)) == 0) {
        
        singleLeftRotationRB(root, doubleBlackNode->father);
        enum color assistantColor = doubleBlackNode->father->father->color;
        doubleBlackNode->father->father->color = doubleBlackNode->father->color;
        doubleBlackNode->father->color = assistantColor;
        uncle(doubleBlackNode)->color = BLACK;
        
        removeDoubleBlack(root, doubleBlackNode);
        
        return;
    }
}

void removeDoubleBlack (RbNode *root, RbNode doubleBlackNode) {
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

void singleLeftRotationRB (RbNode *root, RbNode pivot) {
    RbNode u, t2;
    
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

void singleRightRotationRB (RbNode *root, RbNode pivot) {
    RbNode u, t1;

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

void doubleLeftRotationRB (RbNode *root, RbNode pivot) {
    RbNode u = pivot->rightNode;
    
    singleRightRotationRB(root, u);
    singleLeftRotationRB(root, pivot);
}

void doubleRightRotationRB (RbNode *root, RbNode pivot) {
    RbNode u = pivot->leftNode;
    
    singleLeftRotationRB(root, u);
    singleRightRotationRB(root, pivot);
}

int isRoot (RbNode root) {
    if (root->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isLeftSon (RbNode root) {
    if (root->father != NULL && root == root->father->leftNode) {
        return 1;
    } else {
        return 0;
    }
}

enum color nodeColor (RbNode root) {
    enum color color;
    
    if (root == NULL) {
        color = BLACK;
    } else {
        color = root->color;
    }
    
    return color;
}

RbNode brother (RbNode root) {
    if (isLeftSon(root) == 1) {
        return root->father->rightNode;
    } else {
        return root->father->leftNode;
    }
}

RbNode uncle (RbNode root) {
    return brother(root->father);
}

AbstractData highestValueRB (RbNode root) {
    if (root->leftNode == NULL && root->rightNode == NULL) {
        return root->data;
    } else {
        if (root->rightNode != NULL) {
            return highestValueRB(root->rightNode);
        } else {
            return root->data;
        }
    }
}

void preOrderRB (RbNode root) {
    if (root != NULL) {
        printf("[%d]", root->data->keyRB);
        preOrderRB(root->leftNode);
        preOrderRB(root->rightNode);
    }
}
