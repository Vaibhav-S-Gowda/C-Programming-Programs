#include <stdio.h>
#include <limits.h>

int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;

        // Check for overflow before it happens
        // INT_MAX (2147483647) / 10 is 214748364
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) {
            return 0;
        }
        // INT_MIN (-2147483648) / 10 is -214748364
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) {
            return 0;
        }

        rev = rev * 10 + pop;
    }
    return rev;
}

int main() {
    int test1 = 123;
    int test2 = -123;
    int test3 = 120;
    int test4 = 1534236469; // Will overflow

    printf("Reverse of %d: %d\n", test1, reverse(test1));
    printf("Reverse of %d: %d\n", test2, reverse(test2));
    printf("Reverse of %d: %d\n", test3, reverse(test3));
    printf("Reverse of %d: %d (Overflow case)\n", test4, reverse(test4));

    return 0;
}