#include <stdio.h>      // Standard input/output functions
#include <stdlib.h>     // For exit() function
#include <math.h>       // (Not needed here actually, but commonly included for pow)
#include <ctype.h>      // For isdigit() function
#define MAX 100         // Defines maximum size of stack and expression

char stack[MAX];        // Stack implemented using an array (stores integers in postfix evaluation)
int top = -1;           // Top pointer initialized to -1 meaning stack is empty

void push(int);         // Function prototype to push an integer into stack
int pop();              // Function prototype to pop an integer from stack

int main(void) {
    char exp[MAX], symbol;   // exp[] holds the postfix expression, symbol holds each character while scanning
    int op2, op1, i;         // Operands and loop index variable

    printf("Enter the postfix expression: ");
    scanf("%s", exp);        // Read postfix expression as string (no spaces allowed here)

    // Scan the postfix expression from left to right
    for(i = 0; exp[i] != '\0'; i++) {
        symbol = exp[i];     // Extract each character

        // Check if this character is a digit (operand)
        if(isdigit(symbol))
            // Convert char digit to integer and push it
            push(symbol - '0');
        else { 
            // If it is an operator, pop two values from stack
            op2 = pop();     // Second operand (right operand)
            op1 = pop();     // First operand (left operand)

            // Perform the operation depending on operator
            switch(symbol) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/': push(op1 / op2); break;

                case '^': {  // Manual power calculation
                    int result = 1;
                    for (int j = 0; j < op2; j++)
                        result *= op1;
                    push(result);
                    break;
                }

                default: // If unknown operator encountered
                    printf("Invalid operator %c\n", symbol);
                    exit(1);
            }
        }
    }

    // After evaluating the whole expression, the result is on top of stack
    printf("Result = %d\n", stack[top]);

    return 0;
}

// Function to push a value into stack
void push(int symbol) {
    if (top == MAX - 1) {       // Check stack overflow
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = symbol;      // Increment top and store the value
}

// Function to pop a value from stack
int pop() {
    if (top == -1) {            // Check stack underflow
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];        // Return value and decrement top
}
