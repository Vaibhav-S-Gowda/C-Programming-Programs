#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *Llink;
    struct node *Rlink;
} *Node;

// Create a new node
Node createNode(int value) {
    Node NN = malloc(sizeof(struct node));
    if (!NN) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    NN->data = value;
    NN->Llink = NN->Rlink = NULL;
    return NN;
}

Node head = NULL;

/* ---------------------- INSERT OPERATIONS ---------------------- */

void insertFront(int value) {
    // Create a new node NN with the given value
    Node NN = createNode(value); // Case 1: If the list is empty (first node)
    if (head == NULL) {        
        head = NN;             // new node becomes head
        NN->Llink = head;      // left link points to itself
        NN->Rlink = head;      // right link also points to itself
        return;
    }
    // Case 2: List already has nodes
    // Because it is circular, head->Llink ALWAYS gives the last node
    Node last = head->Llink; // 1. New node should point to the current head
    NN->Rlink = head; // 2. New node's left link should point to the last node
    NN->Llink = last; // 3. Last node's right link should point to the new node (complete circle)
    last->Rlink = NN; // 4. Old head's left must now point to new node
    head->Llink = NN; // 5. Move head to the new front node
    head = NN;
}

// Insert at rear
void insertRear(int value) {
    Node NN = createNode(value);

    if (head == NULL) {
        head = NN;
        NN->Llink = NN->Rlink = head;
        return;
    }

    Node last = head->Llink;

    NN->Rlink = head;
    NN->Llink = last;
    last->Rlink = NN;
    head->Llink = NN;
}

/* ---------------------- DELETE OPERATIONS ---------------------- */

// Delete front
void deleteFront() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }

    if (head->Rlink == head) {     // Only one node
        free(head);
        head = NULL;
        return;
    }

    Node last = head->Llink;
    Node temp = head;

    head = head->Rlink;
    head->Llink = last;
    last->Rlink = head;

    free(temp);
}

// Delete rear
void deleteRear() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }

    if (head->Rlink == head) {     // One node
        free(head);
        head = NULL;
        return;
    }

    Node last = head->Llink;
    Node secondLast = last->Llink;

    secondLast->Rlink = head;
    head->Llink = secondLast;

    free(last);
}

/* ---------------------- DISPLAY OPERATIONS ---------------------- */

// Forward display
void displayForward() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }

    Node temp = head;
    printf("Forward: ");

    do {
        printf("%d <-> ", temp->data);
        temp = temp->Rlink;
    } while (temp != head);

    printf("(HEAD)\n");
}

// Backward display
void displayBackward() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }

    Node last = head->Llink;
    Node temp = last;

    printf("Backward: ");

    do {
        printf("%d <-> ", temp->data);
        temp = temp->Llink;
    } while (temp != last);

    printf("(TAIL)\n");
}

/* ---------------------- REVERSE CIRCULAR DOUBLY LIST ---------------------- */

void reverse() {
    if (head == NULL || head->Rlink == head)
        return;

    Node curr = head, temp = NULL;

    do {
        // Swap Llink and Rlink
        temp = curr->Llink;
        curr->Llink = curr->Rlink;
        curr->Rlink = temp;

        curr = curr->Llink;  // Move to next original node
    } while (curr != head);

    head = head->Llink; // new head is previous last
}

/* ---------------------- SORT (BUBBLE) ---------------------- */

void sort() {
    if (head == NULL || head->Rlink == head)
        return;

    int swapped;
    Node curr;

    do {
        swapped = 0;
        curr = head;

        do {
            Node next = curr->Rlink;

            if (next != head && curr->data > next->data) {
                int tmp = curr->data;
                curr->data = next->data;
                next->data = tmp;
                swapped = 1;
            }

            curr = curr->Rlink;

        } while (curr->Rlink != head);

    } while (swapped);
}

/* ---------------------- MAIN ---------------------- */

int main() {
    insertRear(40);
    insertRear(10);
    insertFront(5);
    insertRear(25);
    insertRear(15);

    printf("Original List:\n");
    displayForward();
    displayBackward();

    printf("\nAfter Reverse:\n");
    reverse();
    displayForward();
    displayBackward();

    printf("\nAfter Sort:\n");
    sort();
    displayForward();
    displayBackward();

    printf("\nAfter Deleting Front:\n");
    deleteFront();
    displayForward();

    printf("\nAfter Deleting Rear:\n");
    deleteRear();
    displayForward();

    return 0;
}
