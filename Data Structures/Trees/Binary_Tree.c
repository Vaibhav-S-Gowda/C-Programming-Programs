#include <stdio.h>
#include <stdlib.h>

/* ---------- DEFINE TREE NODE ---------- */
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *TreeNode;

/* ---------- CREATE NODE ---------- */
TreeNode createNode(int value) {
    TreeNode newNode = (TreeNode)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory error!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* ---------- INSERT NODE (LEVEL ORDER) ---------- */
TreeNode insert(TreeNode ROOT, int value) {
    TreeNode newNode = createNode(value);
    if (ROOT == NULL)
        return newNode;

    TreeNode queue[100];
    int front = 0, rear = 0;

    queue[rear++] = ROOT;

    while (front < rear) {
        TreeNode temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = newNode;
            return ROOT;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            return ROOT;
        } else {
            queue[rear++] = temp->right;
        }
    }
    return ROOT;
}

/* ---------- DFS (INORDER) ---------- */
void dfs(TreeNode root) {
    if (root == NULL)
        return;

    dfs(root->left);          // Left
    printf("%d ", root->data); // Root
    dfs(root->right);         // Right
}

/* ---------- MAIN FUNCTION ---------- */
int main() {
    TreeNode ROOT = NULL;

    ROOT = insert(ROOT, 10);
    ROOT = insert(ROOT, 20);
    ROOT = insert(ROOT, 30);
    ROOT = insert(ROOT, 40);
    ROOT = insert(ROOT, 50);

    printf("DFS (Inorder Traversal): ");
    dfs(ROOT);

    return 0;
}
