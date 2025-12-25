#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} *Node;

/* --------------------- CREATE NODE --------------------- */
Node createNode(int value) {
    Node NN = malloc(sizeof(struct node));
    if (NN == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    NN->data = value;
    NN->link = NULL;
    return NN;
}

/* --------------------- ENQUEUE --------------------- */
/*
Each priority queue is a normal queue:
- Insert at rear.
*/
void enqueue(Node *front, Node *rear, int value) {
    Node NN = createNode(value);

    if (*rear == NULL) { 
        *front = *rear = NN;
        return;
    }

    (*rear)->link = NN;
    *rear = NN;
}

/* --------------------- DEQUEUE --------------------- */
/*
Removes from front of a given priority level queue.
*/
int dequeue(Node *front, Node *rear) {
    if (*front == NULL) {
        printf("Queue Empty\n");
        return -1;
    }

    Node temp = *front;
    int value = temp->data;

    *front = (*front)->link;
    if (*front == NULL)   // Queue becomes empty
        *rear = NULL;

    free(temp);
    return value;
}

/* ------------------ INSERT BY PRIORITY ------------------ */
void insertPriority(Node *front[], Node *rear[], int priority, int value, int maxP) {
    if (priority < 0 || priority >= maxP) {
        printf("Invalid Priority!\n");
        return;
    }

    enqueue(&front[priority], &rear[priority], value);
    printf("Inserted %d at priority %d\n", value, priority);
}

/* ------------------ DELETE VIA PRIORITY RULE ------------------ */
int deletePriority(Node *front[], Node *rear[], int maxP, int mode) {
    /*
    mode = 0 → ASCENDING PRIORITY (0 is highest)
    mode = 1 → DESCENDING PRIORITY (highest numeric priority first)
    */

    if (mode == 0) {
        // Ascending: Try priority 0,1,2,...
        for (int i = 0; i < maxP; i++) {
            if (front[i] != NULL)
                return dequeue(&front[i], &rear[i]);
        }
    } else {
        // Descending: Try (maxP-1, maxP-2,...)
        for (int i = maxP - 1; i >= 0; i--) {
            if (front[i] != NULL)
                return dequeue(&front[i], &rear[i]);
        }
    }

    printf("All priority queues empty\n");
    return -1;
}

/* ---------------------- DISPLAY ---------------------- */
void displayAll(Node *front[], int maxP) {
    printf("\n***** MULTIPLE PRIORITY QUEUE *****\n");

    for (int i = 0; i < maxP; i++) {
        printf("Priority %d: ", i);
        Node temp = front[i];

        if (temp == NULL) {
            printf("EMPTY\n");
            continue;
        }

        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->link;
        }
        printf("NULL\n");
    }
}

/* ------------------------ MAIN ------------------------ */
int main() {
    int maxP = 4;  // 4 priority levels (0,1,2,3)

    // Arrays of front and rear pointers for each priority
    Node front[maxP], rear[maxP];

    // Initialize all queues as empty
    for (int i = 0; i < maxP; i++) {
        front[i] = rear[i] = NULL;
    }

    insertPriority(front, rear, 0, 10, maxP);
    insertPriority(front, rear, 2, 50, maxP);
    insertPriority(front, rear, 1, 20, maxP);
    insertPriority(front, rear, 3, 70, maxP);
    insertPriority(front, rear, 1, 25, maxP);

    displayAll(front, maxP);

    printf("\nDeleting (Ascending Priority)...\n");
    int val = deletePriority(front, rear, maxP, 0);
    printf("Deleted: %d\n", val);

    displayAll(front, maxP);

    printf("\nDeleting (Descending Priority)...\n");
    val = deletePriority(front, rear, maxP, 1);
    printf("Deleted: %d\n", val);

    displayAll(front, maxP);

    return 0;
}
