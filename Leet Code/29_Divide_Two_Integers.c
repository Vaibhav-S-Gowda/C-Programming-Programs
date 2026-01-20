#include <stdio.h>
#include <limits.h>

int divide(int dividend, int divisor) {
    // Handle overflow case explicitly
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }
    return dividend / divisor;
}

int main() {
    int dividend = -2147483648;
    int divisor  = -1;

    int result = divide(dividend, divisor);

    printf("Result of %d / %d = %d\n", dividend, divisor, result);

    return 0;
}



// Time Complexity: O(1)
// Space Complexity: O(1)