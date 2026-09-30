#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
    int id;
    char name[1000];
    char type[101];
    int quantity;
} Item;

int numOfType = 0;

void updateQuantity(Item list[], int quantityChange) {
    int found = 0;
    char name[1000];
	printf("Nhap ten mat hang: ");
	scanf("%s", name);
    for (int i = 0; i < numOfType; i++) {
        if (strcmp(list[i].name, name) == 0) {
            list[i].quantity += quantityChange;
            if (list[i].quantity < 0) {
                list[i].quantity = 0;
            }
            printf("Da cap nhat so luong cho mat hang ten %s. So luong moi: %d\n", name, list[i].quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay mat hang voi ten %s\n", name);
    }
}

void deleteItem(Item list[]) {
	char name[1000];
	printf("Nhap ten mat hang: ");
	scanf("%s", name);
    int foundIndex = -1;
    for (int i = 0; i < numOfType; i++) {
        if (strcmp(list[i].name, name) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < numOfType - 1; i++) {
            list[i] = list[i + 1];
        }
        numOfType--;
        printf("Da xoa mat hang co ten %s thanh cong.\n", name);
    } else {
        printf("Khong tim thay mat hang co ten %s de xoa.\n", name);
    }
}

void updateStore(Item list[]) {
	char name[1000];
	printf("Nhap ten mat hang: ");
	scanf("%s", name);
    int found = 0;
    for (int i = 0; i < numOfType; i++) {
        if (strcmp(list[i].name, name) == 0) {
            found = 1;
            printf("--- Nhap thong tin moi cho mat hang ten %s ---\n", name);
            printf("Nhap ten moi: ");
            scanf("%s", list[i].name);
            printf("Nhap loai hang moi: ");
            scanf("%s", list[i].type);
            printf("Nhap so luong moi: ");
            scanf("%d", &list[i].quantity);
            printf("Da cap nhat thong tin mat hang thanh cong!\n");
            break;
        }
    }
    if (!found) {
        printf("--- Nhap thong tin moi cho mat hang ten %s ---\n", name);
        	list[numOfType].id = 97000000 + numOfType + 1;
            printf("Nhap ten: ");
            scanf("%s", list[numOfType].name);
            printf("Nhap loai hang: ");
            scanf("%s", list[numOfType].type);
            printf("Nhap so luong: ");
            scanf("%d", &list[numOfType].quantity);
            printf("Da cap nhat thong tin mat hang thanh cong!\n");
            numOfType += 1;
    }
}

int findItem(Item list[]) {
	char name[1000];
	printf("Nhap ten mat hang: ");
	scanf("%s", name);
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
    
    int count = 0;
    for (int i = 0; i < numOfType; i++) {
    	
        if (list[i].quantity < 5) {
        	printf("\n=== CANH BAO MAT HANG SAP HET (SO LUONG < 5) ===\n");
            printf("- ID: %d | Ten: %s | Loai: %s | So luong: %d\n\n", 
                   list[i].id, list[i].name, list[i].type, list[i].quantity);
            count++;
        }
    }
}
void printAllItem(Item list[]){
	char butter[10000];
	if(numOfType != 0) printf("   ID   |             Name             |   Category    |Quantity\n");
	for(int i = 0; i < numOfType; i++){
		sprintf(butter,"%8d|%-30s|%-15s|%-5d", list[i].id, list[i].name, list[i].type, list[i].quantity);
		printf("%s\n",butter);
	}
}

int importFromFile(Item list[]){
	char fileName[1000];
	printf("Nhan ten file: ");
	scanf("%s", fileName);
	
	FILE *f = fopen(fileName,"r");
	if(f == NULL){
		printf("file trong\n");
		return 0;
	}
	
	int numOfFileItem;
	fscanf(f,"%d", &numOfFileItem);
	
	for(int i = 0; i < numOfFileItem; i++){
			fscanf(f,"%d|%[^|]|%[^|]|%d", &list[i].id, list[i].name, list[i].type, &list[i].quantity);
	}
	fclose(f);
	return numOfFileItem;
}

void exportToFile(Item list[]){
	char fileName[1000];
	printf("Nhan ten file: ");
	scanf("%s", fileName);
	char butter[100];
	sprintf(butter,"%s.txt",fileName);
	FILE *f = fopen(butter,"w");
	fprintf(f,"%d\n", numOfType);
	
	for(int i = 0; i < numOfType; i++){
			fprintf(f,"%d|%s|%s|%d\n", list[i].id, list[i].name, list[i].type, list[i].quantity);
	}
	fclose(f);
}

int main() {
    Item *list = malloc(5000 * sizeof(Item));
    int choose;
	while(1){
		printf("---He thong quan ly kho hang---");
		printf("\n1. In ra danh sach hang trong kho\n"
				"2. Tra cuu thong tin hang\n"
				"3. Tang so luong hang\n"
				"4. Giam so luong hang\n"	
				"5. Cap nhat thong tin hang\n"
				"6. Xoa thong tin hang\n"
				"7. Nhap thong tin tu file txt\n"
				"8. Xuat thong tin ra file txt\n");
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choose);
		switch (choose){
			case 1:
				printAllItem(list);
				break;
			case 2:
				findItem(list);
				break;
			case 3: {
				printf("Nhap so luong tang: ");
				int quantity;
				scanf("%d", &quantity);
				updateQuantity(list, quantity);
				break;
			}
			case 4: {
				printf("Nhap so luong giam: ");
				int quantity;
				scanf("%d", &quantity);
				updateQuantity(list, -quantity);
				alarm(list);
				break;
			}
			case 5:
				updateStore(list);
				alarm(list);
				break;
			case 6:
				deleteItem(list);
				break;
			case 7:
				numOfType = importFromFile(list);
				break;
			case 8:
				exportToFile(list);
				break;
			default:
				printf("Lua chon khong hop le! Vui long nhap lai.\n");
				break;
		}
		printf("Nhan enter de tiep tuc...");
		char tmp;
		scanf("%c", &tmp);
		for(int i = 1; i <= 50; i++) printf("\n");
		fflush(stdin);
	}
    return 0;
}
