#include <stdio.h>
#include <stdlib.h>

typedef struct mynode {
    int data;
    struct mynode *link;
} *NODE;

// Function to create a new node
NODE createNode(int data) {
    NODE newNode = (NODE)malloc(sizeof(struct mynode));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// Function to insert at end (for creating the list)
NODE insertEnd(NODE head, int data) {
    NODE newNode = createNode(data);
    if (head == NULL)
        return newNode;
    
    NODE temp = head;
    while (temp->link != NULL)
        temp = temp->link;
    temp->link = newNode;
    return head;
}

// Function to display the linked list
void display(NODE head) {
    NODE temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

// Function to merge two sorted linked lists
NODE mergeSortedLists(NODE list1, NODE list2) {
    // Create a dummy node to simplify logic
    NODE dummy = createNode(0);
    NODE tail = dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->link = list1;
            list1 = list1->link;
        } else {
            tail->link = list2;
            list2 = list2->link;
        }
        tail = tail->link;
    }

    // Attach the remaining nodes
    if (list1 != NULL) tail->link = list1;
    if (list2 != NULL) tail->link = list2;

    NODE mergedHead = dummy->link;
    free(dummy); // remove dummy
    return mergedHead;
}

// Main function
int main() {
    NODE list1 = NULL, list2 = NULL, merged = NULL;

    // First sorted list
    list1 = insertEnd(list1, 1);
    list1 = insertEnd(list1, 3);
    list1 = insertEnd(list1, 5);

    // Second sorted list
    list2 = insertEnd(list2, 2);
    list2 = insertEnd(list2, 4);
    list2 = insertEnd(list2, 6);

    printf("List 1: ");
    display(list1);

    printf("List 2: ");
    display(list2);

    // Merge the lists
    merged = mergeSortedLists(list1, list2);

    printf("Merged Sorted List: ");
    display(merged);

    return 0;
}
