#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- Utility Functions ---

// Helper to create a new node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// --- Solution Logic ---

int calculateSum(struct TreeNode* node, int* maxSum) {
    if (node == NULL) return 0;

    // Post-order traversal: calculate max contribution from subtrees
    // We use max(..., 0) because we ignore paths with negative sums
    int leftMax = max(calculateSum(node->left, maxSum), 0);
    int rightMax = max(calculateSum(node->right, maxSum), 0);

    // Update global maximum if the path through this node is better
    int currentPathSum = node->val + leftMax + rightMax;
    if (currentPathSum > *maxSum) {
        *maxSum = currentPathSum;
    }

    // Return the max path contribution this node can offer to its parent
    return node->val + max(leftMax, rightMax);
}

int maxPathSum(struct TreeNode* root) {
    int maxSum = INT_MIN;
    calculateSum(root, &maxSum);
    return maxSum;
}

// --- Main Execution ---

int main() {
    /* Constructing Example 2 from LeetCode:
              -10
              /  \
             9   20
                /  \
               15   7
    */
    struct TreeNode* root = newNode(-10);
    root->left = newNode(9);
    root->right = newNode(20);
    root->right->left = newNode(15);
    root->right->right = newNode(7);

    int result = maxPathSum(root);

    printf("Maximum Path Sum: %d\n", result); // Expected Output: 42

    // Clean up memory (simple manual free for this example)
    free(root->right->left);
    free(root->right->right);
    free(root->right);
    free(root->left);
    free(root);

    return 0;
}