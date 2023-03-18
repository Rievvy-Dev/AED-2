#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "bst.c"
#include "avl.c"
#include "rb.c"

int initTable (Table table) {
    initBstTree(&table->indexBST);
    initAvlTree(&table->indexAVL);
    initRbTree(&table->indexRB);
    table->dataFile = fopen("storage/data.dat", "a+");
    table->indexBST = loadFileBST(table->indexBST, "storage/indexBST.dat");
    table->indexAVL = loadFileAVL(table->indexAVL, "storage/indexAVL.dat");
    loadFileRB(&table->indexRB, "storage/indexRB.dat");
    if (table->dataFile != NULL)
        return 1;
    else
        return 0;
}

void finishTable (Table table) {
    fclose(table->dataFile);
    saveFileBST(table->indexBST, "storage/indexBST.dat");
    saveFileAVL(table->indexAVL, "storage/indexAVL.dat");
    saveFileRB(table->indexRB, "storage/indexRB.dat");
}

void addStudent (Table table, Student student, int *growUp) {
    if (table->dataFile != NULL) {
        AbstractData newIndex = (AbstractData)malloc(sizeof(struct Index));
        newIndex->keyBST = student->callNumber;
        newIndex->keyAVL = student->age;
        newIndex->keyRB = student->id;
        
        fseek(table->dataFile, 0L, SEEK_END);
        newIndex->indexBST = ftell(table->dataFile);
        newIndex->indexAVL = ftell(table->dataFile);
        newIndex->indexRB = ftell(table->dataFile);
        
        char *studentDatas = "%d:%s:%s:%d:%d\n";
        fprintf(table->dataFile, studentDatas, student->id, student->name, student->motherName, student->callNumber, student->age);

        table->indexBST = insertNodeBST(table->indexBST, newIndex);
        table->indexAVL = insertNodeAVL(table->indexAVL, newIndex, growUp);
        insertNodeRB(&table->indexRB, newIndex);
    }
}

void deleteStudentBST (Table table, int value, int *growUp) {
            Student temp = (Student)malloc(sizeof(struct student));
            temp = getStudentBST(table, value);
            table->indexBST = deleteNodeBST(table->indexBST, temp->callNumber);
            table->indexAVL = deleteNodeAVL(table->indexAVL, temp->age, growUp);
            deleteNodeRB(&table->indexRB, temp->id);
}

void deleteStudentAVL (Table table, int value, int *growUp) {
            Student temp = (Student)malloc(sizeof(struct student));
            temp = getStudentAVL(table, value);
            table->indexBST = deleteNodeBST(table->indexBST, temp->callNumber);
            table->indexAVL = deleteNodeAVL(table->indexAVL, temp->age, growUp);
            deleteNodeRB(&table->indexRB, temp->id);
}

void deleteStudentRB (Table table, int value, int *growUp) {
            Student temp = (Student)malloc(sizeof(struct student));
            temp = getStudentRB(table, value);
            table->indexBST = deleteNodeBST(table->indexBST, temp->callNumber);
            table->indexAVL = deleteNodeAVL(table->indexAVL, temp->age, growUp);
            deleteNodeRB(&table->indexRB, temp->id);
}

Student getStudentBST (Table table, int key) {
    if (table->dataFile != NULL) {
        BstNode temp;
        temp = table->indexBST;
        
        while (temp != NULL) {
            if (temp->data->keyBST == key) {
                Student dataFound = (Student)malloc(sizeof(student));
                char *buffer = (char*)malloc(512 * sizeof(char));
                char *subStr;
                
                fseek(table->dataFile, temp->data->indexBST, SEEK_SET);
                fgets(buffer, 512, table->dataFile);
                
                subStr = strtok(buffer, ":");
                dataFound->id = atoi(subStr);
                       
                subStr = strtok(NULL, ":");
                dataFound->name = strdup(subStr);
                
                subStr = strtok(NULL, ":");
                dataFound->motherName = strdup(subStr);

                subStr = strtok(NULL, ":");
                dataFound->callNumber = atoi(subStr);
                
                subStr = strtok(NULL, ":");
                dataFound->age = atoi(subStr);
                
                free(buffer);
                
                return dataFound;
            }
            else {
                if (key > temp->data->keyBST) {
                    temp = temp->rightNode;
                } else {
                    temp = temp->leftNode;
                }
            }
        }
    }
    return NULL;
}

Student getStudentAVL (Table table, int key) {
    if (table->dataFile != NULL) {
        AvlNode temp;
        temp = table->indexAVL;
        
        while (temp != NULL) {
            if (temp->data->keyAVL == key) {
                Student dataFound = (Student)malloc(sizeof(student));
                char *buffer = (char*)malloc(512 * sizeof(char));
                char *subStr;
                
                fseek(table->dataFile, temp->data->indexAVL, SEEK_SET);
                fgets(buffer, 512, table->dataFile);
                
                subStr = strtok(buffer, ":");
                dataFound->id = atoi(subStr);
                       
                subStr = strtok(NULL, ":");
                dataFound->name = strdup(subStr);
                
                subStr = strtok(NULL, ":");
                dataFound->motherName = strdup(subStr);

                subStr = strtok(NULL, ":");
                dataFound->callNumber = atoi(subStr);
                
                subStr = strtok(NULL, ":");
                dataFound->age = atoi(subStr);
                
                free(buffer);
                
                return dataFound;
            }
            else {
                if (key > temp->data->keyAVL) {
                    temp = temp->rightNode;
                } else {
                    temp = temp->leftNode;
                }
            }
        }
    }
    return NULL;
}

Student getStudentRB (Table table, int key) {
    if (table->dataFile != NULL) {
        RbNode temp;
        temp = table->indexRB;
        
        while (temp != NULL) {
            if (temp->data->keyRB == key) {
                Student dataFound = (Student)malloc(sizeof(student));
                char *buffer = (char*)malloc(512 * sizeof(char));
                char *subStr;
                
                fseek(table->dataFile, temp->data->indexRB, SEEK_SET);
                fgets(buffer, 512, table->dataFile);
                
                subStr = strtok(buffer, ":");
                dataFound->id = atoi(subStr);
                       
                subStr = strtok(NULL, ":");
                dataFound->name = strdup(subStr);
                
                subStr = strtok(NULL, ":");
                dataFound->motherName = strdup(subStr);

                subStr = strtok(NULL, ":");
                dataFound->callNumber = atoi(subStr);
                
                subStr = strtok(NULL, ":");
                dataFound->age = atoi(subStr);
                
                free(buffer);
                
                return dataFound;
            }
            else {
                if (key > temp->data->keyRB) {
                    temp = temp->rightNode;
                } else {
                    temp = temp->leftNode;
                }
            }
        }
    }
    return NULL;
}

Student inputData () {
    Student new = (Student)malloc(sizeof(struct student));
    char* buffer = (char*)malloc(256 * sizeof(char));
    
    getchar();
    printf("Digite o indice do aluno: ");
    scanf("%d", &new->id);
    
    getchar();
    printf("Digite o nome do Aluno: ");
    fgets(buffer, 255, stdin);
    removeEnter(buffer);
    new->name = strdup(buffer);
    
    printf("Digite o nome da mae do aluno: ");
    fgets(buffer, 255, stdin);
    removeEnter(buffer);
    new->motherName = strdup(buffer);
    
    printf("Digite o numero da chamada: ");
    scanf("%d", &new->callNumber);
    
    printf("Digite a idade: ");
    scanf("%d", &new->age);
    
    return new;
}

void removeEnter (char *string) {
   string[strlen(string)-1] = '\0'; 
}

void saveFileBST (BstNode bstRoot, char *path) {
    FILE *file;
    file = fopen(path, "wb");
    
    if (file != NULL) {
        saveFileAuxBST(bstRoot, file);
        fclose(file);
    }
}

void saveFileAVL (AvlNode root, char *path) {
    FILE *file;
    file = fopen(path, "wb");
    
    if (file != NULL) {
        saveFileAuxAVL(root, file);
        fclose(file);
    }
}

void saveFileRB (RbNode root, char *path) {
    FILE *file;
    file = fopen(path, "wb");
    
    if (file != NULL) {
        saveFileAuxRB(root, file);
        fclose(file);
    }
}

void saveFileAuxBST (BstNode root, FILE *file) {
    if (root != NULL) {
        fwrite(root->data, sizeof(struct Index), 1, file);
        saveFileAuxBST(root->leftNode, file);
        saveFileAuxBST(root->rightNode, file);
    }
}

void saveFileAuxAVL (AvlNode root, FILE *file) {
    if (root != NULL) {
        fwrite(root->data, sizeof(struct Index), 1, file);
        saveFileAuxAVL(root->leftNode, file);
        saveFileAuxAVL(root->rightNode, file);
    }
}

void saveFileAuxRB (RbNode root, FILE *file) {
    if (root != NULL) {
        fwrite(root->data, sizeof(struct Index), 1, file);
        saveFileAuxRB(root->leftNode, file);
        saveFileAuxRB(root->rightNode, file);
    }
}

BstNode loadFileBST (BstNode root, char* path) {
    FILE *file;
    file = fopen(path, "rb");
    AbstractData temp;
    
    if (file != NULL) {
        temp = (AbstractData)malloc(sizeof(Index));

        while (fread(temp, sizeof(Index), 1, file)) {
            root = insertNodeBST(root, temp);
            temp = (AbstractData)malloc(sizeof(Index));
        }
        fclose(file);
        
    }
    return root;
}

AvlNode loadFileAVL (AvlNode root, char* path) {
    FILE *file;
    file = fopen(path, "rb");
    AbstractData temp;
    int growUp;
    
    if (file != NULL) {
        temp = (AbstractData)malloc(sizeof(Index));

        while (fread(temp, sizeof(Index), 1, file)) {
            root = insertNodeAVL(root, temp, &growUp);
            temp = (AbstractData)malloc(sizeof(Index));
        }
        fclose(file);
    }
    return root;
}

void loadFileRB (RbNode *root, char* path) {
    FILE *file;
    file = fopen(path, "rb");
    AbstractData temp;
    
    if (file != NULL) {
        temp = (AbstractData)malloc(sizeof(Index));

        while (fread(temp, sizeof(Index), 1, file)) {
            insertNodeRB(root, temp);
            temp = (AbstractData)malloc(sizeof(Index));
        }
        fclose(file);
    }
}

void printElementBST (BstNode root, Table table) {
    Student temp = (Student)malloc(sizeof(struct student));
    char* buffer = (char*)malloc(256 * sizeof(char));
    char *subStr;            
    fseek(table->dataFile, root->data->indexBST, SEEK_SET);
    fgets(buffer, 512, table->dataFile);
                
    subStr = strtok(buffer, ":");
    temp->id = atoi(subStr);
            
    subStr = strtok(NULL, ":");
    temp->name = strdup(subStr);
    
    subStr = strtok(NULL, ":");
    temp->motherName = strdup(subStr);

    subStr = strtok(NULL, ":");
    temp->callNumber = atoi(subStr);
    
    subStr = strtok(NULL, ":");
    temp->age = atoi(subStr);
    
    free(buffer);
    
    printf("[Chave: %d, ID: %d, Nome: %s, Nome da mae: %s, Numero da chamada: %d, Idade: %d]\n", root->data->keyBST, temp->id, temp->name, temp->motherName, temp->callNumber, temp->age);
    
    free(temp);
}

void printElementAVL (AvlNode root, Table table) {
    Student temp = (Student)malloc(sizeof(struct student));
    char* buffer = (char*)malloc(256 * sizeof(char));
    char *subStr;            
    fseek(table->dataFile, root->data->indexAVL, SEEK_SET);
    fgets(buffer, 512, table->dataFile);
                
    subStr = strtok(buffer, ":");
    temp->id = atoi(subStr);
            
    subStr = strtok(NULL, ":");
    temp->name = strdup(subStr);
    
    subStr = strtok(NULL, ":");
    temp->motherName = strdup(subStr);

    subStr = strtok(NULL, ":");
    temp->callNumber = atoi(subStr);
    
    subStr = strtok(NULL, ":");
    temp->age = atoi(subStr);
    
    free(buffer);
    
    printf("[Chave: %d, ID: %d, Nome: %s, Nome da mae: %s, Numero da chamada: %d, Idade: %d]\n", root->data->keyAVL, temp->id, temp->name, temp->motherName, temp->callNumber, temp->age);
    
    free(temp);
}

void printElementRB (RbNode root, Table table) {
    Student temp = (Student)malloc(sizeof(struct student));
    char* buffer = (char*)malloc(256 * sizeof(char));
    char *subStr;            
    fseek(table->dataFile, root->data->indexRB, SEEK_SET);
    fgets(buffer, 512, table->dataFile);
                
    subStr = strtok(buffer, ":");
    temp->id = atoi(subStr);
            
    subStr = strtok(NULL, ":");
    temp->name = strdup(subStr);
    
    subStr = strtok(NULL, ":");
    temp->motherName = strdup(subStr);

    subStr = strtok(NULL, ":");
    temp->callNumber = atoi(subStr);
    
    subStr = strtok(NULL, ":");
    temp->age = atoi(subStr);
    
    free(buffer);
    
    printf("[Chave: %d, ID: %d, Nome: %s, Nome da mae: %s, Numero da chamada: %d, Idade: %d]\n", root->data->keyRB, temp->id, temp->name, temp->motherName, temp->callNumber, temp->age);
    
    free(temp);
}

void inOrderBST (BstNode root, Table table) {
    if (root != NULL) {
        inOrderBST(root->leftNode, table);
        printElementBST(root, table);
        inOrderBST(root->rightNode, table);
    }
}

void inOrderAVL (AvlNode root, Table table) {
    if (root != NULL) {
        inOrderAVL(root->leftNode, table);
        printElementAVL(root, table);
        inOrderAVL(root->rightNode, table);
    }
}

void inOrderRB (RbNode root, Table table) {
    if (root != NULL) {
        inOrderRB(root->leftNode, table);
        printElementRB(root, table);
        inOrderRB(root->rightNode, table);
    }
}

void printMenu () {
    printf("\n");
    printf("===========================================\n");
    printf("|-------------Menu de Opções--------------|\n");
    printf("| 1. Adicionar aluno                      |\n");
    printf("| 2. Remover aluno pelo numero da chamada |\n");
    printf("| 3. Remover aluno pela idade             |\n");
    printf("| 4. Remover aluno pelo id                |\n");
    printf("| 5. Mostrar alunos em ordem pela chamada |\n");
    printf("| 6. Mostrar alunos em ordem pela idade   |\n");
    printf("| 7. Mostrar alunos em ordem pelo id      |\n");
    printf("| 8. Procurar aluno pela chamada          |\n");
    printf("| 9. Procurar aluno pela idade            |\n");
    printf("| 10. Procurar aluno pelo id              |\n");
    printf("===========================================\n");
    printf("Digite uma das opções acima: ");
}









