#include<stdio.h>
int main()
{
    int a = 10;
    int b = -20;
    printf("a = %+d\n", a); // '+' flag to show sign
    printf("b = %+d\n", b); 

    float num = 3.14159;
    float price1 = 19.99;
    float price2 = 5.5; 
    printf("PI = %f\n", num); //default 6 digits after decimal
    printf("Price 1 = ₹%2.2f\n", price1); //width 2, precision 2
    printf("Price 2 = ₹%2.2f\n", price2); 
    return 0;
}