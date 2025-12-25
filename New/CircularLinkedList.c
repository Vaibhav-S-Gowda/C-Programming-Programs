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

/* ---------------------- INSERT OPERATIONS ---------------------- */

// Insert at front
void insertFront(Node *head, int value) {
    Node NN = createNode(value);

    if (*head == NULL) {          // Empty list
        *head = NN;
        NN->link = *head;
        return;
    }

    Node temp = *head;
    while (temp->link != *head)
        temp = temp->link;

    NN->link = *head;
    temp->link = NN;
    *head = NN;
}

// Insert at rear
void insertRear(Node *head, int value) {
    Node NN = createNode(value);

    if (*head == NULL) {
        *head = NN;
        NN->link = *head;
        return;
    }

    Node temp = *head;
    while (temp->link != *head)
        temp = temp->link;

    temp->link = NN;
    NN->link = *head;
}

/* ---------------------- DELETE OPERATIONS ---------------------- */

// Delete front
void deleteFront(Node *head) {
    if (*head == NULL) {
        printf("List empty\n");
        return;
    }

    if ((*head)->link == *head) {     // Single node
        free(*head);
        *head = NULL;
        return;
    }

    Node temp = *head;
    Node last = *head;

    while (last->link != *head)
        last = last->link;

    *head = (*head)->link;
    last->link = *head;

    free(temp);
}

// Delete rear
void deleteRear(Node *head) {
    if (*head == NULL) {
        printf("List empty\n");
        return;
    }

    if ((*head)->link == *head) {     // Single node
        free(*head);
        *head = NULL;
        return;
    }

    Node temp = *head;
    Node prev = NULL;

    while (temp->link != *head) {
        prev = temp;
        temp = temp->link;
    }

    prev->link = *head;
    free(temp);
}

/* ---------------------- DISPLAY ---------------------- */

void display(Node head) {
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

/* ---------------------- REVERSE ---------------------- */

void reverse(Node *head) {
    if (*head == NULL || (*head)->link == *head)
        return;

    Node prev = NULL, curr = *head, next;

    do {
        next = curr->link;
        curr->link = prev;
        prev = curr;
        curr = next;
    } while (curr != *head);

    // Old head becomes last node, so connect to new head
    (*head)->link = prev;

    // Update head
    *head = prev;
}


/* ---------------------- SORT ---------------------- */

void sort(Node head) {
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
    Node head = NULL;  // ✔ Local head, no globals

    insertRear(&head, 30);
    insertRear(&head, 10);
    insertFront(&head, 5);
    insertRear(&head, 20);

    printf("Original List:\n");
    display(head);

    printf("\nAfter Reverse:\n");
    reverse(&head);
    display(head);

    printf("\nAfter Sort:\n");
    sort(head);
    display(head);

    printf("\nAfter Deleting Front:\n");
    deleteFront(&head);
    display(head);

    printf("\nAfter Deleting Rear:\n");
    deleteRear(&head);
    display(head);

    return 0;
}
