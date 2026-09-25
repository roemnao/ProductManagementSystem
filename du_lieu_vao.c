#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    int quantity;
    float price;
} Product;

void importData(Product list[], int *n) {
    int inputQuantity;
    printf(""); 
    scanf("%d", &inputQuantity);

    for (int i = 0; i < inputQuantity; i++) {
        if (*n >= 100) {
            printf(""); 
            break;
        }
        printf(""); 
        printf(""); 
        scanf("%s", list[*n].id);

        while (getchar() != '\n'); 

        printf(""); 
        fgets(list[*n].name, sizeof(list[*n].name), stdin);
        list[*n].name[strcspn(list[*n].name, "\n")] = '\0';

        printf(""); 
        scanf("%d", &list[*n].quantity);

        printf(""); 
        scanf("%f", &list[*n].price);

        (*n)++;
    }
    printf(""); 

    FILE *f = fopen("kho_hang.txt", "w");
    if (f != NULL) {
        for (int i = 0; i < *n; i++) {
            fprintf(f, "%s|%s|%d|%.2f\n", list[i].id, list[i].name, list[i].quantity, list[i].price);
        }
        fclose(f);
        printf(""); 
    } else {
        printf(""); 
    }
}
