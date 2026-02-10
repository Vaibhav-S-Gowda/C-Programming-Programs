#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100

// Stack structure — NO GLOBALS USED
typedef struct {
    int arr[MAX_SIZE];
    int top;
    int current_min;
    int current_max;
} Stack;

// Initialize stack
void init(Stack *s) {
    s->top = -1;
    s->current_min = INT_MAX;
    s->current_max = INT_MIN;
}

// Check empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check full
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Push
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow! Cannot push %d.\n", value);
        return;
    }

    s->arr[++(s->top)] = value;
    printf("Pushed %d onto the stack.\n", value);

    // Update min and max
    if (value < s->current_min)
        s->current_min = value;

    if (value > s->current_max)
        s->current_max = value;
}

// Pop
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;
    }

    int popped_value = s->arr[(s->top)--];
    printf("Popped %d from the stack.\n", popped_value);

    // Re-evaluate min and max if necessary
    if (!isEmpty(s)) {
        if (popped_value == s->current_min) {
            s->current_min = INT_MAX;
            for (int i = 0; i <= s->top; i++)
                if (s->arr[i] < s->current_min)
                    s->current_min = s->arr[i];
        }
        if (popped_value == s->current_max) {
            s->current_max = INT_MIN;
            for (int i = 0; i <= s->top; i++)
                if (s->arr[i] > s->current_max)
                    s->current_max = s->arr[i];
        }
    } else {
        // Reset if stack becomes empty
        s->current_min = INT_MAX;
        s->current_max = INT_MIN;
    }

    return popped_value;
}

// Peek
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return s->arr[s->top];
}

// Get minimum
int getMin(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack empty! No minimum.\n");
        return -1;
    }
    return s->current_min;
}

// Get maximum
int getMax(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack empty! No maximum.\n");
        return -1;
    }
    return s->current_max;
}

/* ---------------------- MAIN ---------------------- */

int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 5);
    push(&s, 20);

    printf("Top element: %d\n", peek(&s));
    printf("Minimum element: %d\n", getMin(&s));
    printf("Maximum element: %d\n", getMax(&s));

    pop(&s);

    printf("Minimum element: %d\n", getMin(&s));
    printf("Maximum element: %d\n", getMax(&s));

    push(&s, 2);

    printf("Minimum element: %d\n", getMin(&s));
    printf("Maximum element: %d\n", getMax(&s));

    return 0;
}
