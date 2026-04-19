#include <stdio.h>
#include <stdlib.h> // For llabs()

int mirrorDistance(int n) {
    long long original = n;
    long long reversed = 0;
    long long temp = n;

    // Reverse the digits of n
    while (temp > 0) {
        reversed = reversed * 10 + (temp % 10);
        temp /= 10;
    }

    // Calculate the absolute difference
    long long diff = original - reversed;
    
    return (int)llabs(diff);
}

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    int result = mirrorDistance(n);

    printf("Mirror Distance: %d\n", result);

    return 0;
}