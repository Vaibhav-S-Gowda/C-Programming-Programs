#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} *Node;

// Create a new node
Node createNode(int value) {
    Node NN = malloc(sizeof(struct node));
    if (!NN) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    NN->data = value;
    NN->link = NULL;
    return NN;
}

Node head = NULL;   // Circular linked list head

/* ---------------------- INSERT OPERATIONS ---------------------- */

// Insert at front
void insertFront(int value) {
    Node NN = createNode(value);

    if (head == NULL) {          // Empty list
        head = NN;
        NN->link = head;
        return;
    }

    Node temp = head;
    while (temp->link != head)
        temp = temp->link;

    NN->link = head;
    temp->link = NN;
    head = NN;
}

// Insert at rear
void insertRear(int value) {
    Node NN = createNode(value);

    if (head == NULL) {
        head = NN;
        NN->link = head;
        return;
    }

    Node temp = head;
    while (temp->link != head)
        temp = temp->link;

    temp->link = NN;
    NN->link = head;
}

/* ---------------------- DELETE OPERATIONS ---------------------- */

// Delete front
void deleteFront() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }

    if (head->link == head) {     // Single node
        free(head);
        head = NULL;
        return;
    }

    Node temp = head;
    Node last = head;

    while (last->link != head)
        last = last->link;

    head = head->link;
    last->link = head;

    free(temp);
}

// Delete rear
void deleteRear() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }

    if (head->link == head) {     // Single node
        free(head);
        head = NULL;
        return;
    }

    Node temp = head;
    Node prev = NULL;

    while (temp->link != head) {
        prev = temp;
        temp = temp->link;
    }

    prev->link = head;   // Last → head
    free(temp);
}

/* ---------------------- DISPLAY ---------------------- */

void display() {
    if (head == NULL) {
        printf("List Empty\n");
        return;
    }

    Node temp = head;
    printf("Circular List: ");

    do {
        printf("%d -> ", temp->data);
        temp = temp->link;
    } while (temp != head);

    printf("(HEAD)\n");
}

/* ---------------------- REVERSE CIRCULAR LIST ---------------------- */
void reverse() {
    if (head == NULL || head->link == head)
        return;

    Node prev = NULL, curr = head, next;

    Node last = head;
    while (last->link != head)
        last = last->link;

    do {
        next = curr->link;
        curr->link = prev;
        prev = curr;
        curr = next;
    } while (curr != head);

    head->link = prev;  // Old head now points to last node
    head = prev;        // New head
}

/* ---------------------- SORT (BUBBLE) ---------------------- */
void sort() {
    if (head == NULL || head->link == head)
        return;

    int swapped;
    Node curr, next;
    do {
        swapped = 0;
        curr = head;

        do {
            next = curr->link;

            if (next != head && curr->data > next->data) {
                int temp = curr->data;
                curr->data = next->data;
                next->data = temp;
                swapped = 1;
            }

            curr = curr->link;
        } while (curr->link != head);

    } while (swapped);
}

/* ---------------------- MAIN ---------------------- */

int main() {
    insertRear(30);
    insertRear(10);
    insertFront(5);
    insertRear(20);

    printf("Original List:\n");
    display();

    printf("\nAfter Reverse:\n");
    reverse();
    display();

    printf("\nAfter Sort:\n");
    sort();
    display();

    printf("\nAfter Deleting Front:\n");
    deleteFront();
    display();

    printf("\nAfter Deleting Rear:\n");
    deleteRear();
    display();

    return 0;
}
