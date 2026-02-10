#include <stdio.h>
#include <stdlib.h>

typedef struct myStack {
    int *arr;
    int top;
    int capacity;
} *Stack;

// Initialize stack
void init(Stack s, int initialSize) {
    s->arr = malloc(initialSize * sizeof(int));
    s->top = -1;
    s->capacity = initialSize;
}

// Resize stack (double capacity)
void resize(Stack s) {
    s->capacity *= 2;
    s->arr = realloc(s->arr, s->capacity * sizeof(int));
    printf("Stack resized to %d\n", s->capacity);
}

// PUSH
void push(Stack s, int value) {
    if (s->top == s->capacity - 1) {
        resize(s);
    }
    s->arr[++s->top] = value;
    printf("%d pushed\n", value);
}

// POP
int pop(Stack s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}

// PEEK
int peek(Stack s) {
    if (s->top == -1) {
        printf("Stack empty\n");
        return -1;
    }
    return s->arr[s->top];
}

// isEmpty
int isEmpty(Stack s) {
    return s->top == -1;
}

// DISPLAY
void display(Stack s) {
    if (s->top == -1) {
        printf("Stack empty\n");
        return;
    }

    printf("Stack (Top -> Bottom): ");
    for (int i = s->top; i >= 0; i--)
        printf("%d ", s->arr[i]);
    printf("\n");
}

int main() {
    // s is already a pointer because of typedef
    Stack s = malloc(sizeof(struct myStack));

    init(s, 3);  // initial size

    push(s, 10);
    push(s, 20);
    push(s, 30);
    push(s, 40); // triggers resize

    display(s);

    printf("Popped: %d\n", pop(s));
    display(s);

    printf("Top element: %d\n", peek(s));

    free(s->arr); // free dynamic array
    free(s);      // free stack structure

    return 0;
}
