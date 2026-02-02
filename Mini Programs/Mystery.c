#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int x = 5;

    // The "Goes To" operator (x goes to 0)
    // and the "Reversed Array" indexing
    while (x --> 0) {
        printf("Value at index %d is: %d\n", x, x[numbers]);
    }

    return 0;
}