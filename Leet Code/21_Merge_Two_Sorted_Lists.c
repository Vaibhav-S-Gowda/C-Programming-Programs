#include <stdio.h>
#include <stdlib.h>

/* Definition for singly-linked list */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // Dummy node to simplify edge cases (empty result list)
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    // Merge while both lists have remaining nodes
    while (list1 != NULL && list2 != NULL) {
        // Attach the node with the smaller value
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        // Move tail to the last node of the merged list
        tail = tail->next;
    }

    // Attach the remaining nodes (only one list can be non-empty)
    if (list1 != NULL)
        tail->next = list1;
    else
        tail->next = list2;

    // Head of merged list is next of dummy
    return dummy.next;
}

/* Helper function to create a new node */
struct ListNode* createNode(int val) {
    struct ListNode* node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

/* Helper function to print a linked list */
void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    // Create first sorted list: 1 -> 3 -> 5
    struct ListNode* list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);

    // Create second sorted list: 2 -> 4 -> 6
    struct ListNode* list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);

    // Merge the two sorted lists
    struct ListNode* merged = mergeTwoLists(list1, list2);

    // Print the merged list
    printf("Merged list: ");
    printList(merged);

    return 0;
}


/*
- A dummy node avoids special handling of the head
- tail always points to the last node of the merged list
- At each step, attach the smaller node
- When one list ends, attach the rest of the other list
- Return dummy.next as the merged list head
*/

/*
    Complexity
        Time Complexity: O(n + m)
        Space Complexity: O(1) (in-place, no new nodes created)
*/