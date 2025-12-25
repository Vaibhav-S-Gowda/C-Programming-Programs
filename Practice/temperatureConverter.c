#include<stdio.h>
#include<string.h>

int main()
{

    //Temperature Conversion Program

    char choice = '\0';
    float fahrenheit = 0.0f;
    float celsius = 0.0f;

    printf("Temperature Conversion Program\n");
    printf("C. Celsius to Fahrenheit\n");
    printf("F. Fahrenheit to Celsius\n");
    printf("Is the temperature in Celsius (C) or Fahrenheit (F)?:");
    scanf("%c",&choice);

    while (choice != 'C' && choice != 'F' && choice != 'c' && choice != 'f')
    {
        printf("Invalid choice!\nPlease select C or F: ");
        scanf("%c",&choice);
    }

    if (choice == 'C' || choice == 'c')
    {
        printf("Enter the temperature in Celsius: ");
        scanf("%f",&celsius);
        fahrenheit = (celsius * 9 / 5) + 32; // C to F
        printf("%.1f Celsius is equal to %.1f Fahrenheit\n", celsius, fahrenheit);
    }
    else
    {
        printf("Enter the temperature in Fahrenheit: ");
        scanf("%f",&fahrenheit);
        celsius = (fahrenheit - 32) * 5 / 9; // C to F
        printf("%.1f Fahrenheit is equal to %.1f Celsius\n", fahrenheit, celsius);
    }
    
    return 0;
}