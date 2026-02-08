#include <stdio.h>
#include <stdlib.h>

typedef struct mynode {
    int data;
    struct mynode *link;
} *NODE;

// Create a new node
NODE createNode(int data) {
    NODE newNode = (NODE)malloc(sizeof(struct mynode));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// Insert at end
NODE insertEnd(NODE head, int data) {
    NODE newNode = createNode(data);
    if (head == NULL) return newNode;

    NODE temp = head;
    while (temp->link != NULL) temp = temp->link;
    temp->link = newNode;
    return head;
}

// Display linked list
void display(NODE head) {
    NODE temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

// Reverse linked list
NODE reverseList(NODE head) {
    NODE prev = NULL, curr = head, next = NULL;

    while (curr != NULL) {
        next = curr->link;   // Store next node
        curr->link = prev;   // Reverse the link
        prev = curr;         // Move prev forward
        curr = next;         // Move curr forward
    }

    return prev;  // New head
}

// Main function
int main() {
    NODE head = NULL;

    // Creating list
    head = insertEnd(head, 1);
    head = insertEnd(head, 2);
    head = insertEnd(head, 3);
    head = insertEnd(head, 4);

    printf("Original List: ");
    display(head);

    head = reverseList(head);

    printf("Reversed List: ");
    display(head);

    return 0;
}
