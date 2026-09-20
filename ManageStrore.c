#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Item {
    int ID; // ma so 10 kitu
    char Name[101];
    char Type[101];
    int Quantity;
} Item;
int NumofType;

void Update(Item _list[], char _name[], int QuantityChange) {
    int existed = 0;

    for (int i = 0; i < NumofType; i++) {
        if (strcmp(_list[i].Name, _name) == 0) {
            _list[i].Quantity += QuantityChange;
            existed = 1;
        }
    }

    if (existed == 0) {
        int newID;
        char newType[101];
        scanf("%d %s", &newID, newType);
        (NumofType)++;
        _list[NumofType - 1].ID = newID;
        strcpy(_list[NumofType - 1].Name, _name);
        strcpy(_list[NumofType - 1].Type, newType);
        _list[NumofType - 1].Quantity = QuantityChange;
        
    }
}


void Alarm(){
	
}
void importFromFile(){
	scanf("%d", &NumofType);

    Item List[NumofType + 10];

    for (int i = 0; i < NumofType; i++) {
        scanf("%d %s %s %d", &List[i].ID, List[i].Name, List[i].Type, &List[i].Quantity);
    }
}
void importToFile(){
	
}
int main() {
    
    

    char test_name[1000];
    scanf("%s", test_name);

    FindItem(List, test_name);
    printf("#\n");
    Update(List, test_name, 100);
    printf("#\n");
	FindItem(List, test_name);
    return 0;
}
