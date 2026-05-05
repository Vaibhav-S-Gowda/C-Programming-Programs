#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || !head->next || k == 0) {
        return head;
    }

    struct ListNode *tail = head;
    int length = 1;

    while (tail->next) {
        tail = tail->next;
        length++;
    }

    k = k % length;
    if (k == 0) {
        return head;
    }

    tail->next = head;

    struct ListNode *newTail = head;
    for (int i = 0; i < length - k - 1; i++) {
        newTail = newTail->next;
    }

    head = newTail->next;
    newTail->next = NULL;

    return head;
}

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Helper: Print the list
void printList(struct ListNode* head) {
    while (head) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {

    struct ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    int k = 2;
    printf("Original list: ");
    printList(head);

    head = rotateRight(head, k);

    printf("Rotated by %d: ", k);
    printList(head);

    return 0;
}