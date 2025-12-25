#include <stdio.h>

#define MAX 100

// Insert a value into the binary tree array
void insert(int tree[], int *size, int value) {
    if (*size >= MAX) {
        printf("Tree overflow! Cannot insert.\n");
        return;
    }
    tree[(*size)++] = value;
}

// Display the tree in level order
void display(int tree[], int size) {
    if (size == 0) {
        printf("Tree is empty!\n");
        return;
    }
    printf("Binary Tree (Level Order): ");
    for (int i = 0; i < size; i++)
        printf("%d ", tree[i]);
    printf("\n");
}

// Utility Functions to find relations
int parent(int index)     { return (index - 1) / 2; }
int leftChild(int index)  { return 2 * index + 1; }
int rightChild(int index) { return 2 * index + 2; }

// Display Node Relationship
void displayNodeRelations(int tree[], int size, int index) {
    if (index < 0 || index >= size) {
        printf("Invalid index!\n");
        return;
    }

    printf("\nNode at index %d: %d\n", index, tree[index]);

    // Parent
    if (index > 0)
        printf(" Parent: %d\n", tree[parent(index)]);

    // Left Child
    if (leftChild(index) < size)
        printf(" Left Child: %d\n", tree[leftChild(index)]);

    // Right Child
    if (rightChild(index) < size)
        printf(" Right Child: %d\n", tree[rightChild(index)]);
}

// Driver Code
int main() {
    int tree[MAX];
    int size = 0;

    // Insert sample nodes
    insert(tree, &size, 10);
    insert(tree, &size, 20);
    insert(tree, &size, 30);
    insert(tree, &size, 40);
    insert(tree, &size, 50);
    insert(tree, &size, 60);

    // Display tree
    display(tree, size);

    // Display relationships of index 1 (value 20)
    displayNodeRelations(tree, size, 1);

    return 0;
}
