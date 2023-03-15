#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb.h"

int main(int argc, char * argv[]) {
	Tree root;
	int option, value;
	initNode(&root);

	while (true) {
		scanf("%d", &option);

		switch (option) {
            case 1:
                scanf("%d", &value);
                insertNode(&root, value);
                break;
            case 2:
                scanf("%d", &value);
                deleteNode(&root, value);
                break;
            case 3:
                preOrder(root);
                break;
            case 99:
                exit(0);
		}
	}
}
