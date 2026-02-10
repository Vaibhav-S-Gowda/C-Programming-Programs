#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = 0, rear = -1;

int isFull() {
    return rear == MAX - 1;
}

int isEmpty() {
    return front > rear;
}

void enqueue(int x) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    queue[++rear] = x;
    printf("%d enqueued\n", x);
}

int dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return -1;
    }
    printf("%d dequeued\n", queue[front]);
    return queue[front++];
}

void display() {
    if (isEmpty()) {
        printf("Queue Empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(50);
    enqueue(60);
    enqueue(70);
    display();
    
    dequeue();
    enqueue(40);
    display();

    return 0;
}
