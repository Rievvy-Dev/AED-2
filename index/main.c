#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "index.h"

int main (int argc, char * argv[]) {
    int option;
    int *growUp = malloc(sizeof(int));
    Student student;
    table table;
    initTable(&table);
    

    
    while (true) {
        
        printMenu();
        scanf("%d", &option);
        
        switch (option) {
            int value;
            
            case 1:
                printf("\n");
                addStudent(&table ,inputData(), growUp);
                break;
            case 2:
                printf("\n");
                printf("Digite o numero da chamada do aluno que deseja remover: ");
                scanf("%d", &value);
                deleteStudentBST(&table, value, growUp);
                break;
            case 3: 
                printf("\n");
                printf("Digite a idade do aluno que deseja remover: ");
                scanf("%d", &value);
                deleteStudentAVL(&table, value, growUp);
                break;
            case 4:
                printf("\n");
                printf("Digite o id do aluno que deseja remover: ");
                scanf("%d", &value);
                deleteStudentRB(&table, value, growUp);
                break;
            case 5:
                printf("\n");
                printf("inOrderBST: \n");
                inOrderBST(table.indexBST, &table);
                printf("\n");
                break;
            case 6:
                printf("\n");
                printf("inOrderAVL: \n");
                inOrderAVL(table.indexAVL, &table);
                printf("\n");
                break;
            case 7:
                printf("\n");
                printf("inOrderRB: \n");
                inOrderRB(table.indexRB, &table);
                printf("\n");
                break;
            case 8:
                printf("\n");
                printf("Procurar Aluno pela BST usando o Numero da chamada: ");
                scanf("%d", &value);
                student = getStudentBST(&table, value);
                
                if (student != NULL) {
                    printf("\nId: %d\nNome: %s\nNome da mae: %s\nNumero da chamada: %d\nIdade: %d\n", student->id, student->name, student->motherName, student->callNumber, student->age);
                } else {
                    printf("Aluno não encontrado");
                }
                break;
            case 9:
                printf("\n");
                printf("Procurar Aluno pela AVL usando a Idade: ");
                scanf("%d", &value);
                student = getStudentAVL(&table, value);
                
                if (student != NULL) {
                    printf("\nId: %d\nNome: %s\nNome da mae: %s\nNumero da chamada: %d\nIdade: %d\n", student->id, student->name, student->motherName, student->callNumber, student->age);
                } else {
                    printf("Aluno não encontrado");
                }
                break;
            case 10:
                printf("\n");
                printf("Procurar Aluno pela RB usando o ID: ");
                scanf("%d", &value);
                student = getStudentRB(&table, value);
                
                if (student != NULL) {
                    printf("\nId: %d\nNome: %s\nNome da mae: %s\nNumero da chamada: %d\nIdade: %d\n", student->id, student->name, student->motherName, student->callNumber, student->age);
                } else {
                    printf("Aluno não encontrado");
                }
                break;
            case 99:
                finishTable(&table);
                exit(0);
        }
    }
}
