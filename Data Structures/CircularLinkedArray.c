#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define NULL_INDEX -1

int dataArr[MAX];
int nextArr[MAX];

int head = NULL_INDEX;    // Head of circular linked list
int freeIndex = 0;        // Next free index to allocate a node

// Allocate a new node
int getNode(int value) {
    if (freeIndex >= MAX) {
        printf("Memory Full\n");
        return NULL_INDEX;
    }
    int index = freeIndex;
    dataArr[index] = value;
    nextArr[index] = NULL_INDEX;
    freeIndex++;
    return index;
}

// Insert at REAR of circular list
void insertRear(int value) {
    int newNode = getNode(value);
    if (newNode == NULL_INDEX) return;

    if (head == NULL_INDEX) {
        head = newNode;
        nextArr[newNode] = head;
        return;
    }

    int temp = head;
    while (nextArr[temp] != head)
        temp = nextArr[temp];

    nextArr[temp] = newNode;
    nextArr[newNode] = head;
}

// Insert at FRONT
void insertFront(int value) {
    int newNode = getNode(value);
    if (newNode == NULL_INDEX) return;

    if (head == NULL_INDEX) {
        head = newNode;
        nextArr[newNode] = head;
        return;
    }

    int last = head;
    while (nextArr[last] != head)
        last = nextArr[last];

    nextArr[newNode] = head;
    nextArr[last] = newNode;
    head = newNode;
}

// Delete FRONT
void deleteFront() {
    if (head == NULL_INDEX) {
        printf("List Empty\n");
        return;
    }

    int temp = head;

    if (nextArr[head] == head) { // Single node
        head = NULL_INDEX;
        return;
    }

    int last = head;
    while (nextArr[last] != head)
        last = nextArr[last];

    head = nextArr[head];
    nextArr[last] = head;
}

// Delete REAR
void deleteRear() {
    if (head == NULL_INDEX) {
        printf("List Empty\n");
        return;
    }

    if (nextArr[head] == head) { // Single node
        head = NULL_INDEX;
        return;
    }

    int temp = head;
    int prev = NULL_INDEX;

    while (nextArr[temp] != head) {
        prev = temp;
        temp = nextArr[temp];
    }

    nextArr[prev] = head;
}

// Display circular list
void display() {
    if (head == NULL_INDEX) {
        printf("List Empty\n");
        return;
    }

    int temp = head;
    do {
        printf("%d -> ", dataArr[temp]);
        temp = nextArr[temp];
    } while (temp != head);
    printf("(HEAD)\n");
}

// Reverse the circular linked list
void reverse() {
    if (head == NULL_INDEX || nextArr[head] == head)
        return;

    int prev = NULL_INDEX;
    int curr = head;
    int next;

    do {
        next = nextArr[curr];
        nextArr[curr] = prev;
        prev = curr;
        curr = next;
    } while (curr != head);

    nextArr[head] = prev;  // old head points to last
    head = prev;           // new head
}

// Sort the circular linked list (ascending)
void sort() {
    if (head == NULL_INDEX || nextArr[head] == head)
        return;

    int swapped;
    int tempData;

    do {
        swapped = 0;
        int curr = head;

        do {
            int next = nextArr[curr];
            if (next != head && dataArr[curr] > dataArr[next]) {
                tempData = dataArr[curr];
                dataArr[curr] = dataArr[next];
                dataArr[next] = tempData;
                swapped = 1;
            }
            curr = next;
        } while (curr != head);
    } while (swapped);
}

int main() {
    insertRear(40);
    insertRear(10);
    insertFront(5);
    insertRear(20);

    printf("Original List:\n");
    display();

    printf("\nAfter Reverse:\n");
    reverse();
    display();

    printf("\nAfter Sort:\n");
    sort();
    display();

    printf("\nAfter Deleting Front:\n");
    deleteFront();
    display();

    printf("\nAfter Deleting Rear:\n");
    deleteRear();
    display();

    return 0;
}
