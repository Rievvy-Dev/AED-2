//Este arquivo é apenas para a inicialização do programa
//Deverá conter apenas um menu simples para testes das funções implementadas no arquivo bst.c

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    Tree new, aux;
    new = NULL;
    aux = NULL;
    int option, value;
    int controllBalance;
    
    while (option != 99) {
        scanf("%d", &option);
        switch (option) {
            case 1:
                scanf("%d", &value);
                new = insertNode(new, value, &controllBalance);
                break;
            case 2:
                scanf("%d", &value);
                new = deleteNode(new, value, &controllBalance);
                break;
            case 3:
                preOrder(new);
                printf("\n");
                break;
            case 4:
                inOrder(new);
                printf("\n");
                break;
            case 5:
                posOrder(new);
                printf("\n");
                break;
            case 6:
                printf("Search a node: ");
                scanf("%d", &value);
                aux = searchNode(new, value);
                printf("%d\n", aux->value);
                break;
            case 7:
                printf("The highest value is: %d\n", highestValue(new));
                break;
            case 8:
                descending(new);
                printf("\n");
            case 99:
                exit(0);
        }
    }
    
    return 0;
}
