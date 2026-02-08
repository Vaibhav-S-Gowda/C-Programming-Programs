#include<stdio.h>
#include<stdlib.h> // <-- needed for malloc(), free(), exit()

typedef struct Node
{
    int data;
    struct Node* link; // Pointing to the next node
                       // struct Node* link → 8 bytes (on 64-bit systems) So total ≈ 12 or 16 bytes, depending on padding.
} *Node;

//Create a Node
Node Create_Node(int data)
{
    Node newNode = malloc(sizeof(struct Node)); // Allocate Memory
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode -> data = data; //Assign data
    newNode -> link = NULL; //Initialize next pointer
    return newNode;         // Return created node
}

int main() {
    Node first = Create_Node(10); //Deferences the pointer
    printf("Node created with data: %d\n", first->data);
    free(first); // Free allocated memory
    return 0;
}