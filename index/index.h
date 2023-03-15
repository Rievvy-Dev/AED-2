#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>

enum color{BLACK, RED, DOUBLE_BLACK};

typedef struct student {
    int id;
    char * name;
    char * motherName;
    int callNumber;
    int age;
} student;

typedef student * Student;

typedef struct Index {
    int keyBST;
    int keyAVL;
    int keyRB;
    int indexBST;
    int indexAVL;
    int indexRB;
} Index;

typedef Index * AbstractData;

typedef struct bstNode {
    AbstractData data;
    struct bstNode *leftNode;
    struct bstNode *rightNode;
} bstNode;

typedef bstNode * BstNode;

typedef struct avlNode {
    AbstractData data;
    int balance;
    struct avlNode *leftNode;
    struct avlNode *rightNode;
} avlNode;

typedef avlNode * AvlNode;

typedef struct rbNode {
    AbstractData data;
    enum color color;
    struct rbNode* leftNode;
    struct rbNode* rightNode;
    struct rbNode* father;
} rbNode;

typedef rbNode * RbNode;

typedef struct table {
    FILE *dataFile;
    BstNode indexBST;
    AvlNode indexAVL;
    RbNode indexRB;
} table;

typedef table * Table;

int initTable(Table table);

Student inputData();

void finishTable(Table table);

void addStudent(Table table, Student student, int *growUp);

void removeEnter(char *string);

void printElement(BstNode bstNode, Table table);

void inOrder(BstNode root, Table table);

void posOrder(BstNode root, Table table);

void deleteStudentBST(Table table, int value, int *growUp);

AbstractData getIndexBST(Table table, int value);

// BST:

////

AbstractData getIndexAVL (Table table, int key);

AbstractData getIndexRB (Table table, int key);

////

void initBstTree(BstNode *root);

BstNode insertNodeBST(BstNode root, AbstractData data);

BstNode deleteNodeBST(BstNode root, AbstractData data);

AbstractData highestValueBST(BstNode root);

void preOrderBst(BstNode bstRoot, Table table);

void saveFileBST(BstNode root, char *path);

void saveFileAuxBST(BstNode root, FILE *file);

BstNode loadFileBST(BstNode root, char *path);

Student getStudentBST (Table table, int key);

// AVL:

void initAvlTree(AvlNode *root);

AvlNode insertNodeAVL(AvlNode root, AbstractData data, int *growUp);

AvlNode deleteNodeAvl(AvlNode root, AbstractData data, int *decreased);

AvlNode singleLeftRotationAVL(AvlNode root);

AvlNode singleRightRotationAVL(AvlNode root);

AvlNode doubleLeftRotationAVL(AvlNode root);

AvlNode doubleRightRotationAVL(AvlNode root);

AbstractData highestValueAVL(AvlNode root);

AvlNode loadFileAVL(AvlNode root, char *path);

AvlNode rotation(AvlNode root);

void saveFileAVL(AvlNode root, char *path);

void saveFileAuxAVL(AvlNode root, FILE *file);

void preOrderAVL(AvlNode root);

Student getStudentAVL (Table table, int key);

// RB:

void initRbTree(RbNode *root);

void insertNodeRB(RbNode *root, AbstractData data);

void fixInsert(RbNode *root, RbNode node);

void deleteNodeRB(RbNode *root, AbstractData data);

void fixDelete(RbNode *root, RbNode doubleBlackNode);

void removeDoubleBlack(RbNode *root, RbNode doubleBlackNode);

void singleLeftRotationRB(RbNode *root, RbNode pivot);

void singleRightRotationRB(RbNode *root, RbNode pivot);

void doubleLeftRotationRB(RbNode *root, RbNode pivot);

void doubleRightRotationRB(RbNode *root, RbNode pivot);

void preOrderRB(RbNode root);

AbstractData highestValueRB(RbNode root);

enum color nodeColor(RbNode root);

int isRoot(RbNode root);

int isLeftSon(RbNode root);

RbNode brother(RbNode root);

RbNode uncle(RbNode root);

void saveFileRB(RbNode root, char *path);

void saveFileAuxRB(RbNode root, FILE *file);

void loadFileRB(RbNode *root, char*path);

Student getStudentRB (Table table, int key);

#endif
