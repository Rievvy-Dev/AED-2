#include <stdio.h>
#include <stdlib.h>
#include "index.h"

void initAvlTree (AvlNode *root) {
    *root = NULL;
}

AvlNode insertNodeAVL (AvlNode root, AbstractData data, int *growUp) {
    if (root == NULL) {
        AvlNode node = (AvlNode)malloc(sizeof(struct avlNode));
        node->data = data;
        node->leftNode = NULL;
        node->rightNode = NULL;
        node->balance = 0;
        *growUp = 1;
        return node;
    } else {
        if (root->data->keyAVL >= data->keyAVL) {
            root->leftNode = insertNodeAVL(root->leftNode, data, growUp);
            
            if (*growUp) {
                switch (root->balance) {
                    case 0:
                        root->balance = -1;
                        *growUp = 1;
                        break;
                    case -1:
                        *growUp = 0;
                        return rotation(root);
                        break;
                    case 1:
                        root->balance = 0;
                        *growUp = 0;
                        break;
                }
            }
            
        } else {
            root->rightNode = insertNodeAVL(root->rightNode, data, growUp);
            
            if (*growUp) {
                switch (root->balance) {
                    case 0:
                        root->balance = 1;
                        *growUp = 1;
                        break;
                    case -1:
                        root->balance = 0;
                        *growUp = 0;
                        break;
                    case 1:
                        *growUp = 0;
                        return rotation(root);
                }
            }
        }
        return root;
    }
}

AvlNode deleteNodeAVL (AvlNode root, int value, int *decreased) {
    if (root != NULL) {
        if (root->data->keyAVL == value) {
            *decreased = 1;
            
            if (root->leftNode == NULL && root->rightNode == NULL) {
                free(root);
                return NULL;
            } else if (root->leftNode == NULL) {
                AvlNode assistant = root->rightNode;
                free(root);
                return assistant;
            } else if (root->rightNode == NULL) {
                AvlNode assistant = root->leftNode;
                free(root);
                return assistant;
            } else {
                root->data = highestValueAVL(root->leftNode);
                root->leftNode = deleteNodeAVL(root->leftNode, value, decreased);
                
                if (*decreased) {
                    switch (root->balance) {
                        case 0:
                            root->balance = 1;
                            *decreased = 0;
                            break;
                        case -1:
                            root->balance = 0;
                            *decreased = 1;
                            break;
                        case 1:
                            if (root->rightNode->balance != 0) {
                                *decreased = 1;
                            } else {
                                *decreased = 0;
                            }
                            return rotation(root);
                    }
                }
                
                return root;
            }
        } else {
            if (root->data->keyAVL > value) {
                root->leftNode = deleteNodeAVL(root->leftNode, value, decreased);
                
                if (*decreased) {
                    switch (root->balance) {
                        case 0:
                            root->balance = 1;
                            *decreased = 0;
                            break;
                        case -1:
                            root->balance = 0;
                            *decreased = 1;
                            break;
                        case 1:
                            *decreased = 1;
                            return rotation(root);
                    }
                }
            } else {
                root->rightNode = deleteNodeAVL(root->rightNode, value, decreased);
                
                if (*decreased) {
                    switch (root->balance) {
                        case 0:
                            root->balance = -1;
                            *decreased = 0;
                            break;
                        case -1:
                            *decreased = 1;
                            return rotation(root);
                        case 1:
                            root->balance = 0;
                            *decreased = 1;
                            break;
                    }
                }
            }
            return root;
        }
    }
    return NULL;
}

AbstractData highestValueAVL (AvlNode root) {
    if (root->leftNode == NULL && root->rightNode == NULL) {
        return root->data;
    } else {
        if (root->rightNode != NULL) {
            return highestValueAVL(root->rightNode);
        } else {
            return root->data;
        }
    }
}

AvlNode singleLeftRotationAVL (AvlNode root) {
    AvlNode pivot, u, temp;
    
    // Se eu tenho o fator de balanço do pai +2 e o filho +1, tenho uma rotação simples para a esquerda
    
    pivot = root;
    u = pivot->rightNode;
    temp = u->leftNode;
    
    pivot->rightNode = temp;
    u->leftNode = pivot;
    
    if (u->balance == 1) {
        pivot->balance = 0;
        u->balance = 0;
    } else {
        // Para o caso de remoção onde o fator de balanço de "u" pode ser igual a 0;
        
        pivot->balance = 1;
        u->balance = -1;
    }
    
    return u;
    
}

AvlNode singleRightRotationAVL (AvlNode root) {
    AvlNode pivot, u, temp;
    
    // Se meu fator de balanço da raiz for -2, e o filho "u" tiver fator de balanço igual a -1, tenho uma rotação simples para a direita
    
    // Marcando os ponteiros
    pivot = root;
    u = pivot->leftNode;
    temp = u->rightNode;
    
    // Atualizando ponteiros
    pivot->leftNode = temp;
    u->rightNode = pivot;
    
    // Atualizando fator de balanço dos ponteiros
    if (u->balance == -1) {
        pivot->balance = 0;
        u->balance = 0;
    } else {
        // Para o caso de remoção em que o "u" tem fator de balanço 0 antes da rotação;
        
        pivot->balance = -1;
        u->balance = 1;
    }
    
    return u;
}

AvlNode doubleLeftRotationAVL (AvlNode root) {
    AvlNode pivot, u, v;
    
    // Se meu fator de balanço do pivô for +2 mas o fator de balanço do meu "u" for -1, temos uma rotação dupla para a esquerda
    
    // Marcando os ponteiros
    pivot = root;
    u = pivot->rightNode;
    v = u->leftNode;
    
    // Atualizando ponteiros
    pivot->rightNode = v->leftNode;
    v->leftNode = pivot;
    u->leftNode = v->rightNode;
    v->rightNode = u;
    
    // Atualizando fator de balanço dos ponteiros
    if (v->balance == 1) {
        pivot->balance = -1;
        u->balance = 0;
        v->balance = 0;
    } else if (v->balance == -1) {
        pivot->balance = 0;
        u->balance = 1;
        v->balance = 0;
    } else {
        pivot->balance = 0;
        u->balance = 0;
        v->balance = 0;
    }
    
    return v;
}

AvlNode doubleRightRotationAVL (AvlNode root) {
    AvlNode pivot, u, v;
    
    // Se meu fator de balanço do pivô for -2 mas o fator de balanço do meu "u" for +1, temos uma rotação dupla para a esquerda
    
    // Marcando os ponteiros
    pivot = root;
    u = pivot->leftNode;
    v = u->rightNode;
    
    // Atualizando ponteiros
    pivot->leftNode = v->rightNode;
    v->rightNode = pivot;
    u->rightNode = v->leftNode;
    v->leftNode = u;
    
    // Atualizando fator de balanço dos ponteiros
    if (v->balance == 1) {
        pivot->balance = 0;
        u->balance = -1;
        v->balance = 0;
    } else if (v->balance == -1) {
        pivot->balance = 1;
        u->balance = 0;
        v->balance = 0;
    } else {
        pivot->balance = 0;
        u->balance = 0;
        v->balance = 0;
    }
    
    return v;
}

AvlNode rotation (AvlNode root) {
    if (root->balance > 0) {
        switch (root->rightNode->balance) {
            case 0:
                return singleLeftRotationAVL(root);
            case -1:
                return doubleLeftRotationAVL(root);
            case 1:
                return singleLeftRotationAVL(root);
        }
    } else {
        switch (root->leftNode->balance) {
            case 0:
                return singleRightRotationAVL(root);
            case -1:
                return singleRightRotationAVL(root);
            case 1:
                return doubleRightRotationAVL(root);
        }
    }
}

void preOrderAVL (AvlNode root) {
    if (root != NULL) {
        printf("[%d]", root->data->keyAVL);
        preOrderAVL(root->leftNode);
        preOrderAVL(root->rightNode);
    }
}


