#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} *NODE;

// Function to create a new node
NODE getNode(int data) {
    NODE newnode = (NODE)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->link = NULL;
    return newnode;
}

/* --------------------------- COMMON FUNCTIONS --------------------------- */

// Insert at Front (for Output Restricted DEQUE)
NODE insertFront(NODE front, int data) {
    NODE newnode = getNode(data);
    newnode->link = front;
    return newnode;
}

// Insert at Rear
NODE insertRear(NODE front, int data) {
    NODE newnode = getNode(data);

    if (front == NULL)
        return newnode;

    NODE temp = front;
    while (temp->link != NULL)
        temp = temp->link;

    temp->link = newnode;
    return front;
}

// Delete from Front
NODE deleteFront(NODE front) {
    if (front == NULL) {
        printf("\nDeque is empty!\n");
        return NULL;
    }

    NODE temp = front;
    front = front->link;
    printf("\nDeleted from front: %d\n", temp->data);
    free(temp);
    return front;
}

// Delete from Rear
NODE deleteRear(NODE front) {
    if (front == NULL) {
        printf("\nDeque is empty!\n");
        return NULL;
    }

    NODE temp = front, prev = NULL;

    while (temp->link != NULL) {
        prev = temp;
        temp = temp->link;
    }

    if (prev == NULL) {
        printf("\nDeleted from rear: %d\n", temp->data);
        free(temp);
        return NULL;
    }

    printf("\nDeleted from rear: %d\n", temp->data);
    prev->link = NULL;
    free(temp);
    return front;
}

// Display
void display(NODE front) {
    if (front == NULL) {
        printf("\nDeque is empty!\n");
        return;
    }
    printf("\nDeque: ");
    NODE temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

/* --------------------- INPUT RESTRICTED DEQUE --------------------- */
/*
   Insert → only at rear
   Delete → front & rear allowed
*/

void inputRestrictedDeque() {
    NODE front = NULL;
    int choice, data;

    while (1) {
        printf("\n--- Input Restricted Deque ---\n");
        printf("1. Insert at REAR\n");
        printf("2. Delete FRONT\n");
        printf("3. Delete REAR\n");
        printf("4. Display\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            front = insertRear(front, data);
            break;
        case 2:
            front = deleteFront(front);
            break;
        case 3:
            front = deleteRear(front);
            break;
        case 4:
            display(front);
            break;
        case 5:
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}

/* --------------------- OUTPUT RESTRICTED DEQUE --------------------- */
/*
   Delete → only from front
   Insert → front & rear allowed
*/

void outputRestrictedDeque() {
    NODE front = NULL;
    int choice, data;

    while (1) {
        printf("\n--- Output Restricted Deque ---\n");
        printf("1. Insert at FRONT\n");
        printf("2. Insert at REAR\n");
        printf("3. Delete FRONT\n"); 
        printf("4. Display\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            front = insertFront(front, data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            front = insertRear(front, data);
            break;
        case 3:
            front = deleteFront(front);
            break;
        case 4:
            display(front);
            break;
        case 5:
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}

/* --------------------------- MAIN MENU --------------------------- */

int main() {
    int choice;

    while (1) {
        printf("\n=============================\n");
        printf(" DEQUE USING LINKED LIST \n");
        printf("=============================\n");
        printf("1. Input Restricted Deque\n");
        printf("2. Output Restricted Deque\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            inputRestrictedDeque();
            break;
        case 2:
            outputRestrictedDeque();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
