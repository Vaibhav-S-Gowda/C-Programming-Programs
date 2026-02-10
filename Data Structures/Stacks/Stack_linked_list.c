#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} *Node;

Node top = NULL;

// Create a new node
Node createNode(int value) {
    Node NN = malloc(sizeof(struct node));
    if (!NN) {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    NN->data = value;
    NN->link = NULL;
    return NN;
}

// PUSH operation
void push(int value) {
    Node NN = createNode(value);
    NN->link = top;
    top = NN;
    printf("%d pushed\n", value);
}

// POP operation
int pop() {
    if (top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }
    Node temp = top;
    int value = temp->data;
    top = top->link;
    free(temp);
    return value;
}

// PEEK (Top element)
int peek() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}

// CHECK EMPTY
int isEmpty() {
    return top == NULL;
}

// DISPLAY stack
void display() {
    if (top == NULL) {
        printf("Stack is Empty\n");
        return;
    }

    Node temp = top;
    printf("Stack (Top → Bottom): ");

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);

    display();

    printf("Popped: %d\n", pop());
    display();

    printf("Top element: %d\n", peek());

    return 0;
}
