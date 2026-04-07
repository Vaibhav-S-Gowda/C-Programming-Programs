#include <stdio.h>

int main() {
    double number, guess, epsilon;
    
    printf("Enter a number: ");
    scanf("%lf", &number);

    if (number < 0) {
        printf("Square root of negative number is not real.\n");
        return 0;
    }

    // Initial guess
    guess = number / 2.0;
    epsilon = 0.000001;  // precision

    // Newton-Raphson iteration
    while ((guess * guess - number > epsilon) || (number - guess * guess > epsilon)) {
        guess = (guess + number / guess) / 2.0;
    }

    printf("Square root of %.2lf is approximately %.6lf\n", number, guess);

    return 0;
}