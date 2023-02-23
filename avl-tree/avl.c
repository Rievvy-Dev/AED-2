#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

Tree insertNode (Tree root, int value, int *growUp) {
    if (root == NULL) {
        Tree node = (Tree)malloc(sizeof(node));
        node->value = value;
        node->leftNode = NULL;
        node->rightNode = NULL;
        node->balance = 0;
        *growUp = 1;
        return node;
    } else {
        if (root->value >= value) {
            root->leftNode = insertNode(root->leftNode, value, growUp);
            
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
            root->rightNode = insertNode(root->rightNode, value, growUp);
            
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

Tree deleteNode (Tree root, int value, int *decreased) {
    if (root != NULL) {
        if (root->value == value) {
            *decreased = 1;
            
            if (root->leftNode == NULL && root->rightNode == NULL) {
                free(root);
                return NULL;
            } else if (root->leftNode == NULL) {
                Tree assistant = root->rightNode;
                free(root);
                return assistant;
            } else if (root->rightNode == NULL) {
                Tree assistant = root->leftNode;
                free(root);
                return assistant;
            } else {
                root->value = highestValue(root->leftNode);
                root->leftNode = deleteNode(root->leftNode, root->value, decreased);
                
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
            if (root->value > value) {
                root->leftNode = deleteNode(root->leftNode, value, decreased);
                
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
                root->rightNode = deleteNode(root->rightNode, value, decreased);
                
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

Tree singleLeftRotation (Tree root) {
    Tree pivot, u, temp;
    
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

Tree singleRightRotation (Tree root) {
    Tree pivot, u, temp;
    
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

Tree doubleLeftRotation (Tree root) {
    Tree pivot, u, v;
    
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

Tree doubleRightRotation (Tree root) {
    Tree pivot, u, v;
    
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


Tree rotation (Tree root) {
    if (root->balance > 0) {
        switch (root->rightNode->balance) {
            case 0:
                return singleLeftRotation(root);
            case -1:
                return doubleLeftRotation(root);
            case 1:
                return singleLeftRotation(root);
        }
    } else {
        switch (root->leftNode->balance) {
            case 0:
                return singleRightRotation(root);
            case -1:
                return singleRightRotation(root);
            case 1:
                return doubleRightRotation(root);
        }
    }
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

int amountPairs (Tree root) {
    int amount = 0;
    if (root->value%2 == 0) {
        amount++;
        return amount;
    }
}

void descending (Tree root) {
    if (root != NULL) {
        descending(root->rightNode);
        printf("[%d]", root->value);
        descending(root->leftNode);
    }
}

Tree searchNode (Tree root, int value) {
    if (root != NULL) {
        if (root->value == value) {
            return root;
        } else {
            if (root->value > value) {
                root = searchNode (root->rightNode, value);
            } else {
                root = searchNode (root->leftNode, value);
            }
            return root;
        }
    }
    return NULL;
}























