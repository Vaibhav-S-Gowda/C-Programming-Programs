#include<stdio.h>

int main()
{
    //Weight Converter Program
    int choice = 0;
    float pounds = 0.0f;
    float kilograms = 0.0f;
    
    printf("Weight Convertion Calculator\n");
    printf("1. Convert from kilograms to pounds\n");
    printf("2. Convert from pounds to kilograms\n");
    printf("Enter your choice (1 or 2): \n");
    scanf("%d",&choice);

    while(choice != 1 && choice!= 2)
    {
        printf("Enter your choice again(1 or 2): \n");
        scanf("%d",&choice);
    }
    if (choice == 1)
    {
        //Kilograms to pounds
        printf("Enter the weight in kilograms: ");
        scanf("%f",&kilograms);
        pounds = kilograms * 2.20462;
        printf("%.2f kilograms is equal to %.2f pounds",kilograms,pounds);
    }
    else
    {
        //Pounds to kilograms
        printf("Enter the weight in pounds: ");
        scanf("%f",&pounds);
        kilograms = pounds / 2.20462;
        printf("%.2f pounds is equal to %.2f kilograms",pounds,kilograms);
    }
    
    return 0;
}