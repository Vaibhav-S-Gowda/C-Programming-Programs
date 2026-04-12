/*
 * LeetCode 116 — Populate Next Right Pointers in Each Node
 * =========================================================
 * STRATEGY: O(n) time | O(1) space — NO queue, NO recursion stack
 *
 * KEY INSIGHT: Once we connect a level's "next" pointers,
 * that level becomes a FREE linked list we can traverse
 * to wire up the NEXT level below it.
 *
 * We only need two pointers:
 *   leftmost — the first node of the level we are CURRENTLY WIRING
 *   curr     — walks that level rightward via already-set next ptrs
 *
 * PICTURE (perfect binary tree guaranteed):
 *
 *  Level being traversed (curr walks →):
 *       [2] --------next-------> [3] -----> NULL
 *      /   \                   /   \
 *    [4]   [5]               [6]   [7]
 *
 *  For each curr on the parent level we do TWO wires:
 *   Wire 1 (inner children — always exists for perfect tree):
 *       curr->left->next = curr->right
 *
 *   Wire 2 (cross-parent — only when curr->next exists):
 *       curr->right->next = curr->next->left
 *
 *  After the loop, leftmost drops one level: leftmost = leftmost->left
 */

#include <stdio.h>
#include <stdlib.h>

// Definition for a Node.
struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

struct Node* connect(struct Node* root) {

    /*
     * Edge case: empty tree → nothing to do.
     * Also handles the guaranteed-perfect-tree assumption:
     * if root is NULL there are no levels to process.
     */
    if (!root) return NULL;

    /*
     * leftmost tracks the FIRST (leftmost) node of each level.
     * We descend one level per outer-loop iteration.
     *
     * WHY left child?  In a perfect binary tree every internal
     * node has exactly two children, so leftmost->left is always
     * the first node of the level below — no null-check needed
     * until we hit the leaf level (leftmost->left == NULL).
     *
     *   root                   ← leftmost starts here (level 0)
     *   / \
     *  2   3                   ← leftmost becomes root->left next
     * / \ / \
     *4  5 6  7                 ← leftmost becomes 2->left next
     */
    struct Node *leftmost = root;

    /*
     * Outer loop: one iteration per level.
     * Stop when leftmost is a leaf (no children remain to wire).
     *
     * Loop invariant entering each iteration:
     *   - All next pointers ON the current level are already set
     *     (from the previous iteration, or trivially for level 0).
     *   - We are about to set next pointers for the level BELOW.
     */
    while (leftmost->left) {          /* leaf level has no children */

        /*
         * curr walks the CURRENT level left-to-right using the
         * next pointers we set in the previous outer-loop pass.
         *
         * This is the O(1)-space trick: instead of a queue,
         * the already-connected level IS our traversal structure.
         *
         *   curr → [2] → [3] → NULL      (level 1 example)
         *          ↓↓    ↓↓
         *         4  5  6  7             (level 2, to be wired)
         */
        struct Node *curr = leftmost;

        while (curr) {                /* walk until end of this level */

            /* ── Wire 1: left child  →  right child ──────────────────
             *
             *   curr
             *   [2]
             *   / \
             * [4]→[5]     curr->left->next = curr->right
             *
             * Always valid: perfect tree guarantees both children exist
             * whenever curr is not a leaf (outer while guards this).
             */
            curr->left->next = curr->right;

            /* ── Wire 2: right child  →  cousin (cross-parent) ────────
             *
             *   [2] --next--> [3]
             *   / \           / \
             * [4] [5]→→→→→[6] [7]    curr->right->next = curr->next->left
             *
             * Only possible when curr has a right sibling (curr->next != NULL).
             * At the rightmost node of each level curr->next == NULL,
             * and curr->right->next was already initialised to NULL — correct.
             */
            if (curr->next) {
                curr->right->next = curr->next->left;
            }
            /* else: curr->right->next stays NULL (end of its level) ✓ */

            /* Advance to the next node on the CURRENT level */
            curr = curr->next;
        }
        /*
         * Current level is fully wired. Drop down one level.
         * leftmost->left is the first node of the next level
         * (guaranteed non-NULL by outer while condition).
         */
        leftmost = leftmost->left;
    }

    /*
     * All internal levels are connected. Leaf level's next pointers
     * were set in the last iteration of the inner loop and are
     * already correct (all NULL — no children to cross to).
     */
    return root;
}

// --- Helper function to create a new node ---
struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;
    node->left = node->right = node->next = NULL;
    return node;
}

// --- Helper function to print levels using next pointers ---
void printLevelOrder(struct Node* root) {
    struct Node* levelStart = root;
    while (levelStart) {
        struct Node* curr = levelStart;
        while (curr) {
            printf("%d -> ", curr->val);
            if (!curr->next) printf("NULL ");
            curr = curr->next;
        }
        printf("\n");
        levelStart = levelStart->left;
    }
}

int main() {
    // Manually creating a perfect binary tree:
    //      1
    //    /   \
    //   2     3
    //  / \   / \
    // 4   5 6   7
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Connecting nodes...\n");
    connect(root);

    printf("Level-by-level traversal using 'next' pointers:\n");
    printLevelOrder(root);

    return 0;
}

/*
 * ═══════════════════════════════════════════════════════════════
 * WALKTHROUGH on the 4-level tree (nodes 1-15):
 *
 * Pass 1  (leftmost = 1, curr walks: 1)
 *   1->left->next  = 1->right        ⟹  2->next  = 3
 *   curr->next==NULL, skip Wire 2    ⟹  3->next  = NULL (already)
 *   leftmost = 1->left = 2
 *
 * Pass 2  (leftmost = 2, curr walks: 2 → 3 → NULL)
 *   curr=2:
 *     2->left->next  = 2->right      ⟹  4->next  = 5
 *     2->next = 3 ≠ NULL
 *     2->right->next = 3->left       ⟹  5->next  = 6
 *   curr=3:
 *     3->left->next  = 3->right      ⟹  6->next  = 7
 *     3->next==NULL, skip            ⟹  7->next  = NULL (already)
 *   leftmost = 2->left = 4
 *
 * Pass 3  (leftmost = 4, curr walks: 4→5→6→7→NULL)
 *   wires:  8→9,  9→10,  10→11,  11→12,  12→13,  13→14,  14→15
 *   leftmost = 4->left = 8  (leaf → outer while exits)
 *
 * Result:
 *   Level 0:  1→NULL
 *   Level 1:  2→3→NULL
 *   Level 2:  4→5→6→7→NULL
 *   Level 3:  8→9→10→11→12→13→14→15→NULL
 * ═══════════════════════════════════════════════════════════════
 *
 * COMPLEXITY
 * ──────────
 * Time  : O(n)  — every node visited exactly once
 * Space : O(1)  — only two pointer variables, no queue, no recursion
 */