#include<stdio.h>
#include<string.h>
int main()
{
    // Shopping Cart Program
    
    char item[50] = "";
    float price = 0.0f;
    int quantity = 0;
    char currency = '$';
    float total = 0.0f;

    // Input item details
    printf("What item would you like to buy? ");
    fgets(item, sizeof(item), stdin); // Read string with spaces
    item[strlen(item) - 1] = '\0'; // Remove newline character

    printf("What is the price for each?");
    scanf(" %4f", &price); 

    printf("How many would you like to buy?");
    scanf("%d", &quantity); 

    total = price * quantity;
    printf("You have ordered %d %s(s) at a price of %c%.2f each.\n", quantity, item, currency, price);// Display order summary
    printf("Your total is: %c%.2f\n", currency, total); 

    return 0;
}