#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct item{
    int id;
    char name[51];
    char category[51];
    int quantity;

} item;

typedef struct tmpItem{
    char *id;
    char *name;
    char *category;
    char *quantity;
} tmpItem;

int itemCount = 0;
int deletedCount = 0;

#define MAXSTRING 10000
#define BIGINTEGER 999999

tmpItem splitInputedData(char singleData[]){
    tmpItem tmp;
    if(singleData[0] == '|'){
        tmp.id = NULL;
        tmp.name = strtok(singleData, "|\n");
        tmp.category = strtok(NULL, "|\n");
        tmp.quantity = strtok(NULL, "|\n");
    }
    else{
        tmp.id = strtok(singleData, "|\n");
        tmp.name = strtok(NULL, "|\n");
        tmp.category = strtok(NULL, "|\n");
        tmp.quantity = strtok(NULL, "|\n");
    }
    return tmp;
}

void expandMemory(item **storeData, int memoryChange){
    if( -memoryChange > itemCount){
        free(*storeData);
        *storeData = NULL;
    }
    else{
        *storeData = (item *)realloc(*storeData, (itemCount + memoryChange) * sizeof(item));
    }
}   
int checkIDValid(char id[]){
    if(strlen(id) != 8){
        return 0;
    }
    for(int i = 0; i < strlen(id); i++){
        if(id[i] < '0' || id[i] > '9'){
            return 0;
        }
    }
    if(id[0] !='9' || id[1]!='7'){
    	return 0;
	}
    return 1;
}
int checkNameValid(char name[]){
    if(strlen(name) == 0 || strlen(name) > 30){
        return 0;
    }
    for(int i = 0; i < strlen(name); i++){
        if(!((name[i] >= 'a' && name[i] <= 'z')||(name[i] >= 'A' && name[i] <= 'Z')||(name[i] >= '0' && name[i] <= '9')||(name[i] == '_'))){
            return 0;
        }
    }
    int count = 0;
    for(int i = 0; i < strlen(name); i++){
        if((name[i] >= '0' && name[i] <= '9')){
            count += 1;
        }
    }
    if(count == strlen(name)) return 0;
    return 1;
}
int checkCategoryValid(char category[]){
    if(strlen(category) == 0 || strlen(category) > 15){
        return 0;
    }
    for(int i = 0; i < strlen(category); i++){
        if(!((category[i] >= 'a' && category[i] <= 'z')||(category[i] >= '0' && category[i] <= '9'))){
            return 0;
        }
    }
    int count = 0;
    for(int i = 0; i < strlen(category); i++){
        if((category[i] >= '0' && category[i] <= '9')){
            count += 1;
        }
    }
    if(count == strlen(category)) return 0;
    return 1;
}
int checkQuantityValid(char quantity[]){
    if(strlen(quantity) > 5){
        return 0;
    }
    for(int i = 0; i < strlen(quantity); i++){
        if(!(quantity[i] >= '0' || quantity[i] <= '9')){
            return 0;
        }
    }
    return 1;
}
int idToIndex(item *storeData, int id){
    int foundCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (storeData[i].id == id){
            return i;
        }
    }
    return -1;
}
int nameToIndex(item *storeData, char name[]){
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(storeData[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}
int categoryToIndex(item *storeData, char category[], int *listFound){
    int foundCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(storeData[i].category, category) == 0) {
            listFound[foundCount] = i;
            foundCount += 1;
        }
    }
    return foundCount;
}
int quantityToIndex(item *storeData, int quantity, int *listFound){
    int foundCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (storeData[i].quantity == quantity) {
            listFound[foundCount] = i;
            foundCount += 1;
        }
    }
    return foundCount;
}

void addNewItem(item **storeData, tmpItem newItem){
    expandMemory(storeData, 1);
    (*storeData)[itemCount].id = atoi(newItem.id);
    strcpy((*storeData)[itemCount].name, newItem.name);
    strcpy((*storeData)[itemCount].category, newItem.category);
    (*storeData)[itemCount].quantity = atoi(newItem.quantity);
    itemCount += 1;
}
void deleteItem(item **storeData, int itemIndex){
    for(int i = itemIndex; i < itemCount - 1; i++){
        *storeData[i] = *storeData[i+1];
    }
    itemCount -= 1;
    deletedCount += 1;
    *storeData = (item*)realloc(*storeData, itemCount*sizeof(item));
}

int importFromFile(item **storeData, char fileName[]){
    char butter[MAXSTRING];
    tmpItem tmp;
    
    sprintf(butter, "%s.txt", fileName);
    FILE *file = fopen(butter, "r");
    if(file == NULL){
        fclose(file);
        return 1;
    }
    while(fgets(butter, MAXSTRING, file) != NULL){
        tmp = splitInputedData(butter);
        if(checkIDValid(tmp.id) && checkNameValid(tmp.name) && checkCategoryValid(tmp.category) && checkQuantityValid(tmp.quantity)){
            addNewItem(storeData, tmp);
        }
        else{
            fclose(file);
            return -(itemCount+1);
        }
    }
    fclose(file);
    return 0;
}

void exportToFile(item *storeData, char fileName[]){
	char butter[MAXSTRING];
	sprintf(butter,"%s.txt",fileName);
	FILE *file = fopen(butter,"w");
	for(int i = 0; i < itemCount; i++){
			fprintf(file,"%d|%s|%s|%d\n", storeData[i].id, storeData[i].name, storeData[i].category, storeData[i].quantity);
	}
	fclose(file);
}
void printAllItem(item *storeData){
	char butter[MAXSTRING];
	if(itemCount != 0) printf("   ID   |             Name             |   Category    |Quantity\n");
	for(int i = 0; i < itemCount; i++){
		sprintf(butter,"%8d|%-30s|%-15s|%-5d", storeData[i].id, storeData[i].name, storeData[i].category, storeData[i].quantity);
		printf("%s\n",butter);
	}
}
void alarm(item *storeData) {
    int firstTime =0;
    int count = 0;
    char butter[MAXSTRING];
    for (int i = 0; i < itemCount; i++) {
    	
        if (storeData[i].quantity < 5) {
        	if(firstTime==0){ printf("\n=== CANH BAO MAT HANG SAP HET (SO LUONG < 5) ===\n"); firstTime = 1;}
            sprintf(butter,"%8d|%-30s|%-15s|%-5d", storeData[i].id, storeData[i].name, storeData[i].category, storeData[i].quantity);
		    printf("%s\n",butter);
            count++;
        }
    }
}
void printFromIDList(item *storeData, int idList[], int listCount){
    char butter[MAXSTRING];
	if(listCount != 0) printf("   ID   |             Name             |   Category    |Quantity\n");
	for(int i = 0; i < listCount; i++){
		sprintf(butter,"%8d|%-30s|%-15s|%-5d", storeData[idList[i]].id, storeData[idList[i]].name, storeData[idList[i]].category, storeData[idList[i]].quantity);
		printf("%s\n",butter);
	}
}

void updateItemData(item *storeData, int itemIndex, char newName[], char newCategory[], int newQuantity){
    strcpy(storeData[itemIndex].name,newName);
    strcpy(storeData[itemIndex].category,newCategory);
    storeData[itemIndex].quantity = newQuantity;
}
int main(){
    item *storeData = NULL;
    char findBy[MAXSTRING];
    int choose;
	while(choose != 0){
		printf("---He thong quan ly kho hang---\n");
		printf("1. In ra danh sach hang trong kho\n"
				"2. Tra cuu thong tin hang\n"
				"3. Tang so luong hang\n"
				"4. Giam so luong hang\n"	
				"5. Cap nhat thong tin hang\n"
				"6. Xoa thong tin hang\n"
				"7. Nhap thong tin tu file txt\n"
				"8. Xuat thong tin ra file txt\n"
                "0. Thoat\n");
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choose);
		switch (choose){
            case 0: free(storeData); break;
			case 1:
                if(itemCount == 0){
                    printf("Khong co du lieu trong kho.\n");
                    break;
                } 
                else{
                    ("\n---Du lieu trong kho---\n");
                }
				printAllItem(storeData);
				break;
			case 2:{
                printf("Nhap cach tim mat hang(id/name/category/quantity): ");
                scanf("%s",findBy);
				if(strcmp(findBy,"id") == 0){
                    char id[MAXSTRING];
                    scanf("%s",id);
                    if(!checkIDValid(id)){
                        printf("Id khong hop le.\n");
                        break;
                    }
                    else if(idToIndex(storeData,atoi(id)) == -1){
                        printf("Khong tim thay mat hang trong kho.");
                        break;
                    }
                    int listFound[1] = {idToIndex(storeData, atoi(id))};
                    printFromIDList(storeData, listFound, 1);
                }
                else if(strcmp(findBy,"name") == 0){
                    char name[MAXSTRING];
                    scanf("%s",name);
                    if(!checkNameValid(name)){
                        printf("Ten khong hop le.");
                        break;
                    }
                    else if(nameToIndex(storeData,name) == -1){
                        printf("Khong tim thay mat hang trong kho.");
                        break;
                    }
                    int listFound[1] = {idToIndex(storeData, atoi(name))};
                    printFromIDList(storeData, listFound, 1);
                }
                else if(strcmp(findBy,"category") == 0){
                    int listFound[itemCount];
                    char category[MAXSTRING];
                    scanf("%s",category);
                    if(!checkCategoryValid(category)){
                        printf("Loai hang khong hop le.\n");
                        break;
                    }
                    else if(categoryToIndex(storeData,category,listFound) == -1){
                        printf("Khong tim thay mat hang trong kho.");
                        break;
                    }
                    int founedCount = categoryToIndex(storeData, category, listFound);
                    printFromIDList(storeData, listFound, founedCount);
                }
                else if(strcmp(findBy,"quantity") == 0){
                    int listFound[itemCount];
                    char quantity[MAXSTRING];
                    scanf("%s",quantity);
                    if(!checkQuantityValid(quantity)){
                        printf("So luong khong hop le.\n");
                        break;
                    } 
                    else if(quantityToIndex(storeData,atoi(quantity),listFound) == -1){
                        printf("Khong tim thay mat hang trong kho.");
                        break;
                    }
                    int founedCount = quantityToIndex(storeData, atoi(quantity), listFound);
                    printFromIDList(storeData, listFound, founedCount);
                }
                else{
                    printf("Lua chon khong hop le!\n");
                }
				break;
            }
			case 3: {
				printf("Nhap ten mat hang: ");
                char name[MAXSTRING];
				scanf("%s",name);
				if(checkNameValid(name)){
                    printf("Nhap so luong tang: ");
                    char quantity[MAXSTRING];
                    scanf("%s",quantity);
                    if(!(itemCount + atoi(quantity) >= 0 && itemCount + atoi(quantity) <= BIGINTERGER && checkQuantityValid(quantity))){
                        printf("So khong hop le!\n");
                    }
                    else{
                        if(nameToIndex(storeData,name) == -1){
                            printf("Khong tim thay mat hang trong kho.");
                            break;
                        }
                        storeData[nameToIndex(storeData,name)].quantity += atoi(quantity);
                        storeData[nameToIndex(storeData,name)].quantity -= atoi(quantity);
                        int tmp[1] ={nameToIndex(storeData,name)};
                        printFromIDList(storeData, tmp, 1);
                        alarm(storeData);

                    }
                }
				break;
			}
			case 4: {
				printf("Nhap ten mat hang: ");
                char name[MAXSTRING];
				scanf("%s",name);
				if(checkNameValid(name)){
                    printf("Nhap so luong giam: ");
                    char quantity[MAXSTRING];
                    scanf("%s",quantity);
                    if(!(itemCount + atoi(quantity) >= 0 && itemCount + atoi(quantity) <= BIGINTERGER && checkQuantityValid(quantity))){
                        printf("So luong khong hop le!\n");
                    }
                    else{
                        if(nameToIndex(storeData,name) == -1){
                            printf("Khong tim thay mat hang trong kho.");
                            break;
                        }
                        storeData[nameToIndex(storeData,name)].quantity -= atoi(quantity);
                        int tmp[1] ={nameToIndex(storeData,name)};
                        printFromIDList(storeData, tmp, 1);
                        alarm(storeData);
                    }
                }
				break;
			}
			case 5:{
                printf("Nhap ten mat hang: ");
                char name[MAXSTRING];
                scanf("%s",name);
                if(checkNameValid(name)){
                    printf("Nhap ten moi: ");
                    char newName[MAXSTRING];
                    scanf("%s",newName);
                    if(!checkNameValid(newName)){
                        printf("Ten khong hop le!\n");
                        break;
                    }
                    printf("Nhap loai hang moi: ");
                    char newCategory[MAXSTRING];
                    scanf("%s",newCategory);
                    if(!checkCategoryValid(newCategory)){
                        printf("Loai hang khong hop le!\n");
                        break;
                    }
                    printf("Nhap so luong moi: ");
                    char newQuantity[MAXSTRING];
                    scanf("%s",newQuantity);
                    if(!checkQuantityValid(newQuantity)){
                        printf("So luong khong hop le!\n");
                        break;
                    }
                    else if(nameToIndex(storeData,name) == -1){
                        printf("Khonng tim thay mat hang nay trong kho.");
                        break;
                    }
                    updateItemData(storeData, nameToIndex(storeData,name), newName, newQuantity, atoi(newQuantity));
                    printf("Cap nhat mat hang thanh cong\n");
                    int tmp[] = {nameToIndex(storeData,name)};
                    printFromIDList(storeData, tmp, 1);
                }
                else printf("Ten khong hop le!\n");
                break;
            }
			case 6:{
				printf("Nhap ten mat hang: ");
                char name[MAXSTRING];
                scanf("%s",name);
                if(!checkNameValid(name)){
                    printf("Ten khong hop le.\n");
                    break;
                }
                else if(nameToIndex(storeData,name) == -1){
                    printf("Khong tim thay mat hang trong kho.\n");
                    break;
                }
                deleteItem(&storeData, nameToIndex(storeData,name));
                printf("Xoa du lieu cua mat hang thanh cong.\n");
				break;
            }
			case 7:{
			    printf("Nhap ten file txt: ");
                char fileName[MAXSTRING];
                scanf("%s",fileName);
                int error = importFromFile(&storeData, fileName);
                alarm(storeData);
                if(error == 0) printf("Nhap file thanh cong.\n");
                else if(error == 1) printf("File khong co du lieu.\n");
                else if(error == 2) printf("Ten file khong hop le!\n");
                else printf("File co du lieu loi tai dong thu: %d\n", -error);
                
				break;
            }
			case 8:{
				printf("Nhap ten file txt: ");
                char fileName[MAXSTRING];
                scanf("%s",fileName);
                exportToFile(storeData,fileName);
				break;
            }
			default:{
				printf("Lua chon khong hop le! Vui long nhap lai.\n");
				break;
            }
		}
        getc(stdin);
		printf("Nhan enter de tiep tuc...");
        getc(stdin);
		for(int i = 1; i <= 50; i++) printf("\n");

	}
    return 0;
}
