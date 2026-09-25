#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    int quantity;
    float price;
} Product;

void exportData(Product list[], int n) {
    if (n == 0) {
        printf(""); 
    } else {
        printf(""); 
        printf("", "", "", "", "", ""); 
        printf(""); 
        for (int i = 0; i < n; i++) {
            float total = list[i].quantity * list[i].price;
            printf("", list[i].id, list[i].name, list[i].quantity, list[i].price, total);
        }
        printf(""); 
    }
}
