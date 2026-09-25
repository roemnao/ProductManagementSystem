int main() {
    int choice;

    FILE *fileRead = fopen("kho_hang.txt", "r");
    if (fileRead != NULL) {
        char tempId[20], tempName[50];
        int tempQuantity;
        float tempPrice;
        
        while (fscanf(fileRead, " %[^|]| %[^|]| %d| %f\n", tempId, tempName, &tempQuantity, &tempPrice) == 4) {
            updateItem(tempId, tempName, tempQuantity, tempPrice);
        }
        fclose(fileRead);
        printf("[System] Data loaded successfully! Total products: %d\n", itemCount);
    } else {
        printf("[System] No data file found. Starting with an empty list.\n");
    }

    do {
        printf("\n================ INVENTORY MENU ================\n");
        printf("1. Input / Update Product Data\n");
        printf("2. Display Inventory Report\n");
        printf("3. Save Data to File\n");
        printf("4. Search Product by ID\n");
        printf("0. Exit Program\n");
        printf("================================================\n");
        printf("Enter your choice (0-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int inputCount;
                printf("\nHow many products do you want to input? ");
                scanf("%d", &inputCount);

                for (int i = 0; i < inputCount; i++) {
                    char tempId[20], tempName[50];
                    int tempQuantity;
                    float tempPrice;

                    printf("\n--- Input Product (%d/%d) ---\n", i + 1, inputCount);
                    printf("Enter Product ID: ");
                    scanf("%s", tempId);

                    while (getchar() != '\n');
                    printf("Enter Product Name: ");
                    fgets(tempName, sizeof(tempName), stdin);
                    tempName[strcspn(tempName, "\n")] = '\0';

                    printf("Enter Quantity to add: ");
                    scanf("%d", &tempQuantity);

                    printf("Enter Unit Price: ");
                    scanf("%f", &tempPrice);

                    updateItem(tempId, tempName, tempQuantity, tempPrice);
                }
                break;
            }
            case 2: {
                if (itemCount == 0) {
                    printf("\n[Notification] Inventory is currently empty!\n");
                } else {
                    printf("\n==================== INVENTORY STATUS ====================\n");
                    printf("%-12s %-25s %-10s %-12s %-15s\n", "Product ID", "Product Name", "Quantity", "Unit Price", "Total Value");
                    printf("----------------------------------------------------------------------------\n");
                    for (int i = 0; i < itemCount; i++) {
                        float totalValue = itemList[i].quantity * itemList[i].price;
                        printf("%-12s %-25s %-10d %-12.2f %-15.2f\n", 
                               itemList[i].id, itemList[i].name, itemList[i].quantity, itemList[i].price, totalValue);
                    }
                    printf("----------------------------------------------------------------------------\n");
                }
                break;
            }
            case 3: {
                if (itemCount == 0) {
                    printf("\n[Error] No data available to save!\n");
                } else {
                    FILE *fileWrite = fopen("kho_hang.txt", "w");
                    if (fileWrite == NULL) {
                        printf("\n[Error] Could not open file for writing!\n");
                        break;
                    }
                    for (int i = 0; i < itemCount; i++) {
                        fprintf(fileWrite, "%s|%s|%d|%.2f\n", 
                                itemList[i].id, itemList[i].name, itemList[i].quantity, itemList[i].price);
                    }
                    fclose(fileWrite);
                    printf("\n[Success] Data synchronized to 'kho_hang.txt'!\n");
                }
                break;
            }
            case 4: {
                char searchId[20];
                printf("\nEnter Product ID to search: ");
                scanf("%s", searchId);

                int index = findItem(searchId);
                if (index != -1) {
                    printf("\n[Result] Product Found:\n");
                    printf("-> ID: %s\n", itemList[index].id);
                    printf("-> Name: %s\n", itemList[index].name);
                    printf("-> Stock Quantity: %d\n", itemList[index].quantity);
                    printf("-> Unit Price: %.2f\n", itemList[index].price);
                    printf("-> Total Value: %.2f\n", itemList[index].quantity * itemList[index].price);
                } else {
                    printf("\n[Notification] Product ID '%s' not found.\n", searchId);
                }
                break;
            }
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\n[Error] Invalid choice! Please select between 0 and 4.\n");
        }
    } while (choice != 0);

    return 0;
}
