#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct MYQ {
    int front, rear;
    int qarr[MAX];
}*Queue;

int isFull(Queue Q) {
    return (Q->rear + 1) % MAX == Q->front;
}

int isEmpty(Queue Q) {
    return Q->front == -1;
}

void enqueue(Queue Q, int element) {
    if (isFull(Q)) {
        printf("Queue Overflow: Cannot enqueue, the queue is full.\n");
    }
    else {
        if(isEmpty(Q)) {
            Q->front = 0;
        }
        Q->rear = (Q->rear + 1) % MAX;
        Q->qarr[Q->rear] = element;
        printf("Enqueued: %d\n",element); 
    }
}

int dequeue(Queue Q) {
    if (isEmpty(Q)) {
        printf("Queue Underflow: Cannot dequeue, the queue is empty.\n");
        return -1;
    }
    int element = Q->qarr[Q->front];
    if (Q->front == Q->rear) {
        Q->front = Q->rear = -1;
    } 
    else {
        Q->front = (Q->front + 1) % MAX;
    }
    printf("Dequeued: %d\n", element);
    return element;
}

void display(Queue Q) {
    if (isEmpty(Q)) {
        printf("The queue is empty.\n");
        return;
    }
    int i = Q->front; 
    printf("The elements are: \n");
    do
    {
        printf("%d ", Q->qarr[i]);
        i = (i + 1) % MAX;
    } while (i != (Q->rear + 1) % MAX);
    
    printf("\n");
}

int main() {
    Queue myQueue = (Queue)malloc(sizeof(struct MYQ));
    myQueue->front = myQueue->rear = -1;
    // Initial state check
    printf("--- Circular Queue Demonstration (MAX_SIZE = %d) ---\n", MAX);
    display(myQueue); // Should show "Queue is empty."

    // 1. Enqueue elements
    enqueue(myQueue, 10);
    enqueue(myQueue, 20);
    enqueue(myQueue, 30);
    display(myQueue);

    // 2. Dequeue an element
    dequeue(myQueue); // Dequeues 10
    display(myQueue);

    // 3. Enqueue more elements, demonstrating the 'circular' nature
    enqueue(myQueue, 40);
    enqueue(myQueue, 50);
    display(myQueue);

    // 4. Try to enqueue one more element (should trigger Overflow, as it's full)
    enqueue(myQueue, 60); // Queue is full (10, 20, 30, 40, 50 slots are full)
    display(myQueue);

    // 5. Dequeue elements to free up space (10 was already gone)
    dequeue(myQueue); // Dequeues 20
    dequeue(myQueue); // Dequeues 30
    display(myQueue); // Queue now has 40 and 50

    // 6. Enqueue element 60 (should succeed, taking the spot where 20 or 30 was)
    // The new element goes into index 1 or 2, demonstrating wrap-around
    enqueue(myQueue, 60);
    display(myQueue);

    // 7. Dequeue all remaining elements
    dequeue(myQueue); // Dequeues 40
    dequeue(myQueue); // Dequeues 50
    dequeue(myQueue); // Dequeues 60
    display(myQueue); // Should show "Queue is empty."

    // 8. Try to dequeue when empty (should trigger Underflow)
    dequeue(myQueue);

    printf("--- Demonstration Complete ---\n");

    // Free the allocated memory for the queue
    free(myQueue);

    return 0;
}