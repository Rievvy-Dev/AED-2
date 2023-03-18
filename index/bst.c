#include <stdio.h>
#include <stdlib.h>
#include "index.h"

void initBstTree (BstNode *root) {
    *root = NULL;
}

BstNode insertNodeBST (BstNode root, AbstractData data) {
    if (root == NULL) {
        BstNode new = (BstNode)malloc(sizeof(struct bstNode));
        
        new->data = data;
        new->leftNode = NULL;
        new->rightNode = NULL;
        
        return new;
    } else {
        if (data->keyBST > root->data->keyBST) {
            root->rightNode = insertNodeBST(root->rightNode, data);
        } else {
            root->leftNode = insertNodeBST(root->leftNode, data);
        }
        return root;
    }
    
}

BstNode deleteNodeBST (BstNode root, int value) {
    if (root != NULL) {
        if (root->data->keyBST == value) {
            if (root->rightNode == NULL && root->leftNode == NULL) {
                free(root);
                return NULL;
            } else if (root->rightNode != NULL && root->leftNode == NULL) {
                BstNode assistant = root->rightNode;
                free(root);
                return assistant;
            } else if (root->rightNode == NULL && root->leftNode != NULL) {
                BstNode assistant = root->leftNode;
                free(root);
                return assistant;
            } else {
                root->data = highestValueBST(root->leftNode);
                root->leftNode = deleteNodeBST(root->leftNode, value);
                return root;
            }
        } else {
            if (root->data->keyBST < value) {
                root->rightNode = deleteNodeBST(root->rightNode, value);
            } else {
                root->leftNode = deleteNodeBST(root->leftNode, value);
            }
            return root;
        }
    }
    return NULL;
}

AbstractData highestValueBST (BstNode root) {
    AbstractData highest;
    
    if (root->rightNode == NULL) {
        return root->data;
    } else {
        if (root->rightNode != NULL) {
           highest = highestValueBST(root->rightNode); 
        } else {
            return root->data;
        }
    }
}

void preOrderBst (BstNode root, Table table) {
    if (root != NULL) {
        printf("[%d]", root->data->keyBST);
 
//         printElement(root, table);
        preOrderBst(root->leftNode, table);

        preOrderBst(root->rightNode, table);

    }
}


