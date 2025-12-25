// This is the classic Shunting Yard Algorithm by Edsger Dijkstra.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>   // for isdigit()
#define MAX 100

char stack[MAX];
char infix[MAX], postfix[MAX];
int top = -1;

void push(char);
char pop();
int isEmpty();
void inToPost();
int space(char);
void print();
int precedence(char);
int evaluatePostfix(char postfix[]);

int main() {
    printf("Enter the infix expression: ");
    gets(infix);

    inToPost();
    print();

    // printf("Result = %d\n", evaluatePostfix(postfix));
    return 0;
}

void inToPost() {
    int i, j = 0;
    char next;
    char symbol;
    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];
        if(!space(symbol)) { // If symbol is not a white space
            switch (symbol) {
            case '(':
                push(symbol);
                break;

            case ')':
            while ((next = pop()) != '(') 
                postfix[j++] = next;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                //!isEmpty() - Dont't pop from an empty stack
                // precedence(stack[top]) - Operator already in stack
                // precedence(symbol) - current operator being read
                    postfix[j++] = pop();
                push(symbol);
                break;
            default: // If the symbol is an operand
                postfix[j++] = symbol;
            }
        }
    }
    while (!isEmpty())
        postfix[j++] = pop();
    postfix[j] = '\0';
}

int space(char c) {
    return (c == ' ' || c == '\t');
}

int precedence(char symbol) {
    switch(symbol) {
        // Higher value means greater precedence
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void print() {
    int i = 0;
    printf("The equivalent postfix expression is: ");
    while (postfix[i]) 
        printf("%c", postfix[i++]);
    printf("\n");
}

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack Overfow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    char c;
    if(top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

int evaluatePostfix(char postfix[]) {
    int i, op1, op2;
    char symbol;

    for (i = 0; postfix[i] != '\0'; i++) {
        symbol = postfix[i];

        if (isdigit(symbol)) {  
            // convert char digit to int
            push(symbol - '0'); // ASCII value of 1 is 49 and 0 is 48. Hence 49-48 = 1.
        }
        else {  // operator
            op2 = pop();
            op1 = pop();

            switch(symbol) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/': push(op1 / op2); break;
                case '^': {
                    int result = 1;
                    for (int j = 0; j < op2; j++)
                        result *= op1;
                    push(result);
                    break;
                }
                default:
                    printf("Invalid operator %c\n", symbol);
                    exit(1);
            }
        }
    }
    return pop(); // final result
}