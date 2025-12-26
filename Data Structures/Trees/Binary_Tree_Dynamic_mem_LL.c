// implement a Binary Tree using dynamic memory allocation

#include <stdio.h>
#include <stdlib.h>

// Definition of node using typedef
typedef struct mynode {
    int data;                   // Value of the node
    struct mynode* left;        // Pointer to the left child
    struct mynode* right;       // Pointer to the right child
}*TreeNode;

// Function to create a new TreeNode
TreeNode createNode(int value) {
    TreeNode newNode = (TreeNode)malloc(sizeof(struct mynode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert TreeNodes in a Binary Tree (Level Order)
TreeNode insert(TreeNode root, int value) {
    TreeNode newNode = createNode(value);
    if (root == NULL)
        return newNode;

    TreeNode queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = newNode;
            return root;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            return root;
        } else {
            queue[rear++] = temp->right;
        }
    }
    return root;
}

// Tree Traversals
void inorder(TreeNode root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(TreeNode root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Free memory
void freeTree(TreeNode root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Depth-First-Search 
void DFS(TreeNode root) {
    if (root == NULL) return;
    printf("%d", root->data);
    DFS(root->left);
    DFS(root->right);
}

// Main function
int main() {
    TreeNode root = NULL;

    // Sample Insertions
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    int values[] = {11, 8, 5, 9,  12, 45, 67, 90};
    int n = sizeof(values)/sizeof(values[0]);
    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);
    
    printf("DFS: ");
    DFS(root);
    freeTree(root);
    return 0;
}
