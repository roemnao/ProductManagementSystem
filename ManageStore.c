#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[1000];
    char type[101];
    int quantity;
} Item;

#define ID_LENGTH 8
#define NAME_MAX_LENGTH 30
#define TYPE_MAX_LENGTH 15
#define QUANTITY_MAX 99999

static int isErrorShown = 1;

static int isDigitChar(char character) { return character >= '0' && character <= '9'; }
static int isUpperChar(char character) { return character >= 'A' && character <= 'Z'; }
static int isLowerChar(char character) { return character >= 'a' && character <= 'z'; }

int numOfItem = 0;

static void clearInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int expandMemory(Item **list, int delta){
	int newCount = numOfItem + delta;
	if (newCount <= 0) {
		free(*list);
		*list = NULL;
		return 0;
	}
	Item *tmp = realloc(*list, newCount * sizeof(Item));
	if (tmp == NULL) return -1;
	*list = tmp;
	return 0;
}

static void reportError(const char *message)
{
    if (isErrorShown) {
        printf("%s\n", message);
    }
}

int checkIDValid(const char *id)
{
    int isValid = 1;
    int index;

    if (id == NULL || strlen(id) != ID_LENGTH) {
        isValid = 0;
    } else {
        for (index = 0; index < ID_LENGTH; index++) {
            if (!isDigitChar(id[index])) {
                isValid = 0;
                break;
            }
        }
        if (isValid && !(id[0] == '9' && id[1] == '7')) {
            isValid = 0;
        }
    }

    if (!isValid) {
        reportError("Loi, ID phai gom dung 8 chu so, khong chua chu cai hay "
                    "ky tu dac biet, va 2 chu so dau la 97.");
    }
    return isValid;
}

int checkNameValid(const char *name)
{
    int isValid = 1;
    int hasLetter = 0;
    size_t length;
    size_t index;

    if (name == NULL) {
        isValid = 0;
    } else {
        length = strlen(name);
        if (length == 0 || length > NAME_MAX_LENGTH) {
            isValid = 0;
        } else {
            for (index = 0; index < length; index++) {
                if (isUpperChar(name[index]) || isLowerChar(name[index])) {
                    hasLetter = 1;
                } else if (!isDigitChar(name[index]) && name[index] != '_') {
                    isValid = 0;
                    break;
                }
            }
            if (isValid && !hasLetter) {
                isValid = 0;
            }
        }
    }

    if (!isValid) {
        reportError("Loi, Ten phai co tu 1 den 30 ky tu, chi gom chu cai "
                    "(hoa hoac thuong), chu so va dau '_' (khong co dau cach "
                    "hay ky tu dac biet), va co it nhat 1 chu cai.");
    }
    return isValid;
}

int checkTypeValid(const char *type)
{
    int isValid = 1;
    size_t length;
    size_t index;

    if (type == NULL) {
        isValid = 0;
    } else {
        length = strlen(type);
        if (length == 0 || length > TYPE_MAX_LENGTH) {
            isValid = 0;
        } else {
            for (index = 0; index < length; index++) {
                if (!isLowerChar(type[index])) {
                    isValid = 0;
                    break;
                }
            }
        }
    }

    if (!isValid) {
        reportError("Loi, Loai phai co tu 1 den 15 ky tu, chi gom chu cai "
                    "thuong (a-z), khong co chu hoa, chu so, dau cach hay "
                    "ky tu dac biet.");
    }
    return isValid;
}

int checkQuantityValid(int quantity)
{
    int isValid = (quantity >= 0 && quantity <= QUANTITY_MAX);

    if (!isValid) {
        reportError("Loi, So luong phai la so nguyen khong am va co toi da "
                    "5 chu so (tu 0 den 99999).");
    }
    return isValid;
}

int checkItemValid(const char *id, const char *name, const char *type,
                   int quantity)
{
    int savedIsErrorShown = isErrorShown;
    int isValid;

    isErrorShown = 0;
    isValid = checkIDValid(id)
           && checkNameValid(name)
           && checkTypeValid(type)
           && checkQuantityValid(quantity);
    isErrorShown = savedIsErrorShown;

    return isValid;
}

void updateQuantity(Item list[], int quantityChange) {
    int found = 0;
    char name[1000];
	printf("Nhap ten mat hang: ");
	if(scanf("%999s", name) != 1) return;
	if(checkNameValid(name) == 0) return;
    for (int i = 0; i < numOfItem; i++) {
        if (strcmp(list[i].name, name) == 0) {
            list[i].quantity += quantityChange;
            if (list[i].quantity < 0) {
                list[i].quantity = 0;
            }
            if (list[i].quantity > QUANTITY_MAX) {
                list[i].quantity = QUANTITY_MAX;
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

void deleteItem(Item **list) {
	char name[1000];
	printf("Nhap ten mat hang: ");
	if(scanf("%999s", name) != 1) return;
	if(checkNameValid(name) == 0) return;
    int foundIndex = -1;
    for (int i = 0; i < numOfItem; i++) {
        if (strcmp((*list)[i].name, name) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < numOfItem - 1; i++) {
            (*list)[i] = (*list)[i + 1];
        }
		expandMemory(list, -1);
        numOfItem--;
        printf("Da xoa mat hang co ten %s thanh cong.\n", name);
    } else {
        printf("Khong tim thay mat hang co ten %s de xoa.\n", name);
    }
}

void updateStore(Item **list) {
	char name[1000];
	char newName[1000];
	char newType[1000];
	int newQuantity;
	printf("Nhap ten mat hang: ");
	if(scanf("%999s", name) != 1) return;
	if(checkNameValid(name) == 0) return;
    int found = 0;
    for (int i = 0; i < numOfItem; i++) {
        if (strcmp((*list)[i].name, name) == 0) {
            found = 1;
            printf("--- Nhap thong tin moi cho mat hang ten %s ---\n", name);
            printf("Nhap ten moi: ");
            if(scanf("%999s", newName) != 1) return;
            if(checkNameValid(newName) == 0) return;
            printf("Nhap loai hang moi: ");
            if(scanf("%999s", newType) != 1) return;
            if(checkTypeValid(newType) == 0) return;
            printf("Nhap so luong moi: ");
            if(scanf("%d", &newQuantity) != 1) {
                clearInput();
                printf("Loi, so luong phai la so nguyen.\n");
                return;
            }
            if(checkQuantityValid(newQuantity) == 0) return;
            strcpy((*list)[i].name, newName);
            strcpy((*list)[i].type, newType);
            (*list)[i].quantity = newQuantity;
            printf("Da cap nhat thong tin mat hang thanh cong!\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay, da tao mat hang\n---Nhap thong tin moi cho mat hang ten %s---\n", name);
		printf("Nhap ten: ");
		if(scanf("%999s", newName) != 1) return;
		if(checkNameValid(newName) == 0) return;
		printf("Nhap loai hang: ");
		if(scanf("%999s", newType) != 1) return;
		if(checkTypeValid(newType) == 0) return;
		printf("Nhap so luong: ");
		if(scanf("%d", &newQuantity) != 1) {
			clearInput();
			printf("Loi, so luong phai la so nguyen.\n");
			return;
		}
		if(checkQuantityValid(newQuantity) == 0) return;
		if (expandMemory(list, 1) != 0) {
			printf("Khong du bo nho.\n");
			return;
		}
		int newId = 97000000 + numOfItem + 1;
		int exists = 1;
		while (exists) {
			exists = 0;
			for (int i = 0; i < numOfItem; i++) {
				if ((*list)[i].id == newId) {
					exists = 1;
					newId++;
					break;
				}
			}
		}
		(*list)[numOfItem].id = newId;
		strcpy((*list)[numOfItem].name, newName);
		strcpy((*list)[numOfItem].type, newType);
		(*list)[numOfItem].quantity = newQuantity;
		numOfItem += 1;
		printf("Da cap nhat thong tin mat hang thanh cong!\n");
    }
}

int findItemByName(Item list[]) {
	char name[1000];
	printf("Nhap ten mat hang: ");
	if(scanf("%999s", name) != 1) return -1;
	if(checkNameValid(name) == 0) return -1;
    int foundIndex = -1;
    for (int i = 0; i < numOfItem; i++) {
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

int findItemByID(Item list[]) {
	char idStr[1000];

	printf("Nhap ID mat hang: ");
	if(scanf("%999s", idStr) != 1) return -1;
	if(checkIDValid(idStr) == 0) return -1;
    int id = atoi(idStr);
    int foundIndex = -1;
    for (int i = 0; i < numOfItem; i++) {
        if (list[i].id == id) {
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
        printf("Khong tim thay mat hang co ID: %s\n", idStr);
    }
    return foundIndex;
}

int findItemByType(Item list[]) {
	char type[1000];

	printf("Nhap loai mat hang: ");
	if(scanf("%999s", type) != 1) return -1;
	if(checkTypeValid(type) == 0) return -1;
    int foundIndex = -1;
    for (int i = 0; i < numOfItem; i++) {
        if (strcmp(list[i].type, type) == 0) {
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
        printf("Khong tim thay mat hang thuoc loai: %s\n", type);
    }
    return foundIndex;
}

int findItemByQuantity(Item list[]) {
	int quantity;

	printf("Nhap so luong: ");
	if(scanf("%d", &quantity) != 1) {
		clearInput();
		printf("Loi, so luong phai la so nguyen.\n");
		return -1;
	}
	if(checkQuantityValid(quantity) == 0) return -1;
    int foundIndex = -1;
    for (int i = 0; i < numOfItem; i++) {
        if (list[i].quantity == quantity) {
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
        printf("Khong tim thay mat hang co so luong: %d\n", quantity);
    }
    return foundIndex;
}

void findItem(Item list[]) {
	char choice[100];

	printf("Tim kiem theo (name, id, type, quantity): ");
	if(scanf("%99s", choice) != 1) return;

	if (strcmp(choice, "name") == 0) 
		findItemByName(list);
	else if (strcmp(choice, "id") == 0) 
		findItemByID(list);
	else if (strcmp(choice, "type") == 0) 
		findItemByType(list);
	else if (strcmp(choice, "quantity") == 0)
		findItemByQuantity(list);
	else
		printf("Khong hop le.\n");
}

void alarm(Item list[]) {
    
    int count = 0;
    for (int i = 0; i < numOfItem; i++) {
    	
        if (list[i].quantity < 5) {
        	if (count == 0) printf("\n=== CANH BAO MAT HANG SAP HET (SO LUONG < 5) ===\n");
            printf("- ID: %d | Ten: %s | Loai: %s | So luong: %d\n", 
                   list[i].id, list[i].name, list[i].type, list[i].quantity);
            count++;
        }
    }
    if (count > 0) printf("\n");
}

void printAllItem(Item list[]){
	char butter[10000];
	if(numOfItem != 0) printf("   ID   |             Name             |   Category    |Quantity\n");
	for(int i = 0; i < numOfItem; i++){
		sprintf(butter,"%8d|%-30s|%-15s|%-5d", list[i].id, list[i].name, list[i].type, list[i].quantity);
		printf("%s\n",butter);
	}
}

int importFromFile(Item **list){
	char fileName[1000];
	char butter[1010];
	char line[1500];
	char idStr[32];
	Item tmp;
	int total;
	int invalidItems = 0;
	int voidItem = 0;
	printf("Nhan ten file: ");
	if(scanf("%999s", fileName) != 1) return -1;
	sprintf(butter,"%s.txt",fileName);
	FILE *f = fopen(butter,"r");
	if(f == NULL){
		printf("Khong mo duoc file\n");
		return -1;
	}
	
	if(fgets(line, sizeof(line), f) == NULL || sscanf(line, "%d", &total) != 1){
		fclose(f);
		printf("File sai dinh dang\n");
		return -1;
	}
	free(*list);
	*list = NULL;
	numOfItem = 0;
	for(int i = 0; i < total; i++){
		if(fgets(line, sizeof(line), f) == NULL){
			voidItem += total - i;
			break;
		}
		if(sscanf(line, "%d|%999[^|]|%100[^|]|%d", &tmp.id, tmp.name, tmp.type, &tmp.quantity) != 4){
			voidItem += 1;
			continue;
		}
		sprintf(idStr, "%d", tmp.id);
		if(checkItemValid(idStr, tmp.name, tmp.type, tmp.quantity) == 0){
			invalidItems += 1;
			continue;
		}
		if(expandMemory(list, 1) != 0) break;
		(*list)[numOfItem] = tmp;
		numOfItem++;
	}
	printf("Da nhap file, %d du lieu loi, %d du lieu trong.\n", invalidItems, voidItem);
	fclose(f);
	return 0;
}

void exportToFile(Item list[]){
	char fileName[1000];
	char butter[1010];
	printf("Nhan ten file: ");
	if(scanf("%999s", fileName) != 1) return;
	sprintf(butter,"%s.txt",fileName);
	FILE *f = fopen(butter,"w");
	if(f == NULL){
		printf("Khong tao duoc file\n");
		return;
	}
	fprintf(f,"%d\n", numOfItem);
	
	for(int i = 0; i < numOfItem; i++){
			fprintf(f,"%d|%s|%s|%d\n", list[i].id, list[i].name, list[i].type, list[i].quantity);
	}
	fclose(f);
}

int main() {
    Item *list = NULL;
    int choose;
    int result;
	while(1){
		printf("---He thong quan ly kho hang---");
		printf("\n1. In ra danh sach hang trong kho\n"
				"2. Tra cuu thong tin hang\n"
				"3. Tang so luong hang\n"
				"4. Giam so luong hang\n"	
				"5. Cap nhat thong tin hang\n"
				"6. Xoa thong tin hang\n"
				"7. Nhap thong tin tu file txt\n"
				"8. Xuat thong tin ra file txt\n"
				"0. Thoat\n");
		printf("Nhap lua chon cua ban: ");
		result = scanf("%d", &choose);
		if (result == EOF) {
			free(list);
			return 0;
		}
		if (result != 1) {
			clearInput();
			choose = -1;
		}
		switch (choose){
			case 0:
				free(list);
				return 0;
			case 1:
				printAllItem(list);
				break;
			case 2:
				findItem(list);
				break;
			case 3: {
				printf("Nhap so luong tang: ");
				int quantity;
				if (scanf("%d", &quantity) != 1) {
					clearInput();
					printf("Loi, so luong phai la so nguyen.\n");
					break;
				}
				if (checkQuantityValid(quantity) == 0) break;
				updateQuantity(list, quantity);
				break;
			}
			case 4: {
				printf("Nhap so luong giam: ");
				int quantity;
				if (scanf("%d", &quantity) != 1) {
					clearInput();
					printf("Loi, so luong phai la so nguyen.\n");
					break;
				}
				if (checkQuantityValid(quantity) == 0) break;
				updateQuantity(list, -quantity);
				alarm(list);
				break;
			}
			case 5:
				updateStore(&list);
				alarm(list);
				break;
			case 6:
				deleteItem(&list);
				break;
			case 7:
				importFromFile(&list);
				break;
			case 8:
				exportToFile(list);
				break;
			default:
				printf("Lua chon khong hop le! Vui long nhap lai.\n");
				break;
		}
		printf("Nhan enter de tiep tuc...");
		clearInput();
		getchar();
		for(int i = 1; i <= 50; i++) printf("\n");
	}
    return 0;
}