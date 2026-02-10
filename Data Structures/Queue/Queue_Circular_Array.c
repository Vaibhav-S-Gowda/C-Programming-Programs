#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

int isFull() {
    return (rear + 1) % MAX == front;
}

int isEmpty() {
    return front == -1;
}

void enqueue(int x) {
    if (isFull()) {
        printf("Circular Queue Overflow\n");
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % MAX;

    queue[rear] = x;
    printf("%d enqueued\n", x);
}

void dequeue() {
    if (isEmpty()) {
        printf("Circular Queue Underflow\n");
        return;
    }

    printf("%d dequeued\n", queue[front]);

    if (front == rear)
        front = rear = -1;   // reset queue
    else
        front = (front + 1) % MAX;
}

void display() {
    if (isEmpty()) {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();
    dequeue();
    display();

    enqueue(50);
    enqueue(60); // wrap-around
    display();

    return 0;
}
