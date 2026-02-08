#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* link; 
} *Node;

Node Create_Node(int data)
{
    Node newNode = (Node)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("\n No memory allocated");
        exit(1);
    }
    newNode -> data = data;
    newNode -> link = NULL;
    return newNode;
}

Node Insert_at_Front(int data, Node Header)
{
    Node newNode = Create_Node(data);   // Step 1: create new node
    newNode -> link = Header;           // Step 2: point new node to old head
    Header = newNode;                   // Step 3: new node becomes the new head
    return Header;                      // Step 4: return updated head
}

// Example usage
int main() {
    Node head = NULL;                  // Empty list
    head = Insert_at_Front(10, head);     // head -> [10]
    head = Insert_at_Front(20, head);     // head -> [20] -> [10]
    head = Insert_at_Front(30, head);     // head -> [30] -> [20] -> [10]

    // Traverse and print list
    Node temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");

    // Free memory
    while (head != NULL) {
        Node next = head->link;
        free(head);
        head = next;
    }
    return 0;
}
