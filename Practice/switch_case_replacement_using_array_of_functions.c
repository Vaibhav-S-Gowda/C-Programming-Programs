#include <stdio.h>

/* Function declarations */
void add(int a, int b) {
    printf("Addition = %d\n", a + b);
}

void sub(int a, int b) {
    printf("Subtraction = %d\n", a - b);
}

void mul(int a, int b) {
    printf("Multiplication = %d\n", a * b);
}

void divide(int a, int b) {
    if (b == 0) {
        printf("Division by zero not allowed\n");
        return;
    }
    printf("Division = %d\n", a / b);
}

int main() {
    int choice, x, y;

    /* Array of function pointers */
    void (*ops[4])(int, int) = { add, sub, mul, divide };

    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);

    printf("\nChoose operation:\n");
    printf("0 - Add\n1 - Subtract\n2 - Multiply\n3 - Divide\n");
    scanf("%d", &choice);

    if (choice < 0 || choice > 3) {
        printf("Invalid choice\n");
    } else {
        ops[choice](x, y);   // function call using array index
    }

    return 0;
}