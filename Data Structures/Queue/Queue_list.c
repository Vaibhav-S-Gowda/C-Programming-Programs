#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} *Node;

Node front = NULL, rear = NULL;

Node createNode(int value) {
    Node NN = malloc(sizeof(struct node));
    NN->data = value;
    NN->link = NULL;
    return NN;
}

void enqueue(int value) {
    Node NN = createNode(value);
    if (rear == NULL) {    // first node
        front = rear = NN;
    } else {
        rear->link = NN;
        rear = NN;
    }
    printf("%d enqueued\n", value);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue Underflow\n");
        return;
    }

    Node temp = front;
    printf("%d dequeued\n", temp->data);

    front = front->link;
    if (front == NULL)
        rear = NULL;

    free(temp);
}

void display() {
    if (front == NULL) {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue: ");
    Node temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    dequeue();
    display();

    return 0;
}
