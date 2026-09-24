#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
    int id;
    char name[101];
    char type[101];
    int quantity;
} Item;

int numOfType = 0;

void updateQuantity(Item list[], int id, int quantityChange) {
    int found = 0;
    for (int i = 0; i < numOfType; i++) {
        if (list[i].id == id) {
            list[i].quantity += quantityChange;
            if (list[i].quantity < 0) {
                list[i].quantity = 0;
            }
            printf("Da cap nhat so luong cho mat hang ID %d. So luong moi: %d\n", id, list[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay mat hang voi ID: %d\n", id);
    }
}

void deleteItem(Item list[], int id) {
    int foundIndex = -1;
    for (int i = 0; i < numOfType; i++) {
        if (list[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < numOfType - 1; i++) {
            list[i] = list[i + 1];
        }
        numOfType--;
        printf("Da xoá mat hang co ID %d thanh cong.", id);
    } else {
        printf("Khong tim thay mat hang co ID %d de xoá.", id);
    }
}

void updateStore(Item list[], int id) {
    int found = 0;
    for (int i = 0; i < numOfType; i++) {
        if (list[i].id == id) {
            found = 1;
            printf("--- Nhap thong tin moi cho mat hang ID %d ---\n", id);
            printf("Nhap ten moi: ");
            scanf("%100s", list[i].name);
            printf("Nhap loai hang moi: ");
            scanf("%100s", list[i].type);
            printf("Nhap so luong moi: ");
            scanf("%d", &list[i].quantity);
            printf("Da cap nhat thong tin mat hang thanh cong!\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay mat hang co ID %d de cap nhat.\n", id);
    }
}

int findItem(Item list[], char name[]) {
    int foundIndex = -1;
    for (int i = 0; i < numOfType; i++) {
        if (strcmp(list[i].name, name) == 0) {
            printf("--- Thong tin mat hang tim thay ---\n");
            printf("ID: %d\n", list[i].id);
            printf("Ten: %s\n", list[i].name);
            printf("Loai hang: %s\n", list[i].type);
            printf("So luong: %d\n", list[i].quantity);
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        printf("Khong tim thay mat hang co ten: %s\n", name);
    }
    return foundIndex;
}

void alarm(Item list[]) {
    printf("=== CANH BAO MAT HANG SAP HET (SO LUONG < 5) ===\n");
    int count = 0;
    for (int i = 0; i < numOfType; i++) {
        if (list[i].quantity < 5) {
            printf("- ID: %d | Ten: %s | Loai: %s | So luong: %d\n", 
                   list[i].id, list[i].name, list[i].type, list[i].quantity);
            count++;
        }
    }
    if (count == 0) {
        printf("Khong co mat hang nao duoi so luong 5.\n");
    }
}

void importData(Item list[]) {
    printf("Nhap so luong loai mat hang: ");
    scanf("%d", &numOfType);

    for (int i = 0; i < numOfType; i++) {
        printf("Nhap ID, Ten, Loai hang, So luong (cho item %d): ", i + 1);
        scanf("%d %100s %100s %d", &list[i].id, list[i].name, list[i].type, &list[i].quantity);
    }
}

int main() {
    Item list[100];

    importData(list);

    char testName[101];
    printf("\nNhap ten mat hang can tim: ");
    scanf("%100s", testName);

    findItem(list, testName);

    printf("\n--- Cap nhat so luong ---\n");
    updateQuantity(list, 1, 10);

    printf("\n");
    alarm(list);

    printf("\n--- Cap nhat thong tin mat hang ---\n");
    updateStore(list, 1);

    printf("\n--- Xoa mat hang ---\n");
    deleteItem(list, 1);

    return 0;
}