#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// ------------ Function Prototypes ------------
void push(char stack[], int *top, char c);
char pop(char stack[], int *top);
int isEmpty(int top);
void inToPost(char infix[], char postfix[], char stack[], int *top);
int space(char c);
void printPostfix(char postfix[]);
int precedence(char symbol);
int evaluatePostfix(char postfix[], int stack[], int *top);


// ===================== MAIN =====================
int main() {
    char infix[MAX], postfix[MAX];
    char opStack[MAX];      // operator stack for infix→postfix
    int valStack[MAX];      // integer stack for postfix evaluation

    int top1 = -1;  // top for operator stack
    int top2 = -1;  // top for value stack

    printf("Enter the infix expression: ");
    gets(infix);

    inToPost(infix, postfix, opStack, &top1);

    printPostfix(postfix);

    printf("Result = %d\n", evaluatePostfix(postfix, valStack, &top2));

    return 0;
}



// ==================== INFIX → POSTFIX ====================
void inToPost(char infix[], char postfix[], char stack[], int *top) {
    int i, j = 0;
    char next, symbol;

    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];

        if (!space(symbol)) {
            switch (symbol) {

            case '(':
                push(stack, top, symbol);
                break;

            case ')':
                while ((next = pop(stack, top)) != '(')
                    postfix[j++] = next;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (!isEmpty(*top) && 
                       precedence(stack[*top]) >= precedence(symbol)) 
                {
                    postfix[j++] = pop(stack, top);
                }
                push(stack, top, symbol);
                break;

            default: // operand
                postfix[j++] = symbol;
            }
        }
    }

    while (!isEmpty(*top))
        postfix[j++] = pop(stack, top);

    postfix[j] = '\0';
}



// ==================== SUPPORT FUNCTIONS ====================
int space(char c) {
    return (c == ' ' || c == '\t');
}

int precedence(char symbol) {
    switch(symbol) {
        case '^': return 3;
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

void push(char stack[], int *top, char c) {
    if (*top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++(*top)] = c;
}

char pop(char stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[(*top)--];
}

int isEmpty(int top) {
    return top == -1;
}

void printPostfix(char postfix[]) {
    int i = 0;
    printf("The equivalent postfix expression is: ");
    while (postfix[i])
        printf("%c", postfix[i++]);
    printf("\n");
}



// ==================== POSTFIX EVALUATION ====================
int evaluatePostfix(char postfix[], int stack[], int *top) {

    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];

        if (isdigit(symbol)) {
            // convert char digit to integer
            stack[++(*top)] = symbol - '0';
        }
        else {
            int op2 = stack[(*top)--];
            int op1 = stack[(*top)--];

            int result;

            switch(symbol) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;

                case '^': {
                    result = 1;
                    for (int j = 0; j < op2; j++)
                        result *= op1;
                    break;
                }

                default:
                    printf("Invalid operator %c\n", symbol);
                    exit(1);
            }

            // push result back
            stack[++(*top)] = result;
        }
    }
    
    return stack[(*top)--]; // final result
}
