#include <limits.h>

int divide(int dividend, int divisor) {
    // Handle overflow case
    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    // Determine sign of result
    int negative = (dividend < 0) ^ (divisor < 0);

    // Convert to long long to avoid overflow during abs
    long long dvd = llabs((long long)dividend);
    long long dvs = llabs((long long)divisor);

    long long result = 0;

    // Bitwise division
    while (dvd >= dvs) {
        long long temp = dvs;
        long long multiple = 1;

        // Find the largest shift
        while ((temp << 1) <= dvd) {
            temp <<= 1;
            multiple <<= 1;
        }

        dvd -= temp;
        result += multiple;
    }

    // Apply sign
    if (negative)
        result = -result;

    return (int)result;
}

int main() {
    int dividend = -2147483648;
    int divisor  = -1;

    int result = divide(dividend, divisor);

    printf("Result of %d / %d = %d\n", dividend, divisor, result);

    return 0;
}

/*
    - If dividing INT_MIN by -1, return INT_MAX (overflow).
    - Decide if the final answer is negative or positive.
    - Convert numbers to positive to simplify logic.
    - Repeatedly:
        Double the divisor using <<
        Subtract the largest possible chunk from the dividend
        Add the corresponding power of two to the answer
    - Apply the sign and return the result.
*/

/*
    dividend = 10, divisor = 3

    3 << 1 = 6
    3 << 2 = 12 (too big)

    10 - 6 = 4
    result += 2

    4 - 3 = 1
    result += 1

    Final result = 3
*/

/*
Time Complexity (Precise)
    Inner loop shifts at most 31 times
    Outer loop runs at most log₂(dividend) times
*/