#include<stdio.h>
#include<math.h>

int main()
{
    // Compound Interest Calculator in C

    double principal = 0.0; // Initial amount
    double rate = 0.0; // Annual interest rate (in percentage)
    int timesCompounded = 0; // Number of times interest is compounded per year
    int years = 0; // Number of years the money is invested or borrowed
    double amount = 0.0; // Final amount after interest

    // Input from user
    printf("Enter the principal amount: ");
    scanf("%lf", &principal);
    printf("Enter the annual interest rate (in percentage): ");
    scanf("%lf", &rate);
    printf("Enter the number of times interest is compounded per year: ");
    scanf("%d", &timesCompounded);
    printf("Enter the number of years the money is invested or borrowed: ");
    scanf("%d", &years);

    // Convert annual rate from percentage to decimal
    rate = rate / 100.0;

    // Compound Interest Formula: A = P (1 + r/n)^(nt)
    amount = principal * pow((1 + rate / timesCompounded), (timesCompounded * years));

    // Output the final amount
    printf("The amount after %d years is: %.2lf\n", years, amount);
    
    return 0;
}