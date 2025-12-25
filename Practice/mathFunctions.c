#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
     // Math functions in C

    int x = 10, z = -5;
    float y = 3.14f;


    z = abs(z); // Absolute value
    printf("Absolute value: %d\n", z);

    x = sqrt(x); // Square root
    printf("Square root: %d\n", x);

    x = pow(x, 2); // Power
    printf("Power: %d\n", x);

    y = round(y); // Round
    printf("Round: %.2f\n", y);

    y = ceil(y); // Ceiling
    printf("Ceiling: %.2f\n", y);

    y = floor(y); // Floor
    printf("Floor: %.2f\n", y);

    y = log(y); // Natural logarithm
    printf("Natural logarithm: %.2f\n", y);

    return 0;
}