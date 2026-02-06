#include <stdio.h>
#include <stdlib.h>

// ===== Node Structure =====
typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} *NODE;

NODE head = NULL;

// ===== Create Node =====
NODE createNode(int val) {
    NODE newnode = (NODE)malloc(sizeof(struct node));
    if(newnode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newnode->data = val;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

// ===== Insert at Beginning =====
void insertBegin(int val) {
    NODE newnode = createNode(val);

    if(head == NULL) {
        head = newnode;
        return;
    }

    newnode->next = head;
    head->prev = newnode;
    head = newnode;
}

// ===== Insert at End =====
void insertEnd(int val) {
    NODE newnode = createNode(val);

    if(head == NULL) {
        head = newnode;
        return;
    }

    NODE temp = head;
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newnode;
    newnode->prev = temp;
}

// ===== Insert at Position =====
void insertPos(int val, int pos) {
    if(pos == 1) {
        insertBegin(val);
        return;
    }

    NODE newnode = createNode(val);
    NODE temp = head;
    int i;

    for(i = 1; temp != NULL && i < pos-1; i++)
        temp = temp->next;

    if(temp == NULL) {
        printf("Invalid position\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if(temp->next != NULL)
        temp->next->prev = newnode;

    temp->next = newnode;
}

// ===== Delete Beginning =====
void deleteBegin() {
    if(head == NULL) {
        printf("List empty\n");
        return;
    }

    NODE temp = head;
    head = head->next;

    if(head != NULL)
        head->prev = NULL;

    free(temp);
}

// ===== Delete End =====
void deleteEnd() {
    if(head == NULL) {
        printf("List empty\n");
        return;
    }

    NODE temp = head;

    if(temp->next == NULL) {
        head = NULL;
        free(temp);
        return;
    }

    while(temp->next != NULL)
        temp = temp->next;

    temp->prev->next = NULL;
    free(temp);
}

// ===== Delete at Position =====
void deletePos(int pos) {
    if(head == NULL) {
        printf("List empty\n");
        return;
    }

    NODE temp = head;
    int i;

    if(pos == 1) {
        deleteBegin();
        return;
    }

    for(i = 1; temp != NULL && i < pos; i++)
        temp = temp->next;

    if(temp == NULL) {
        printf("Invalid position\n");
        return;
    }

    if(temp->next != NULL)
        temp->next->prev = temp->prev;

    if(temp->prev != NULL)
        temp->prev->next = temp->next;

    free(temp);
}

// ===== Search =====
void search(int key) {
    NODE temp = head;
    int pos = 1;

    while(temp != NULL) {
        if(temp->data == key) {
            printf("Found at position %d\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("Not found\n");
}

// ===== Display Forward =====
void displayForward() {
    NODE temp = head;

    if(temp == NULL) {
        printf("List empty\n");
        return;
    }

    printf("Forward: ");
    while(temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// ===== Display Backward =====
void displayBackward() {
    NODE temp = head;

    if(temp == NULL) {
        printf("List empty\n");
        return;
    }

    while(temp->next != NULL)
        temp = temp->next;

    printf("Backward: ");
    while(temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// ===== Count Nodes =====
void countNodes() {
    NODE temp = head;
    int count = 0;

    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("Total nodes = %d\n", count);
}

// ===== Reverse DLL =====
void reverseList() {
    NODE temp = NULL;
    NODE current = head;

    while(current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if(temp != NULL)
        head = temp->prev;
}

// ===== Main Menu =====
int main() {
    int choice, val, pos;

    while(1) {
        printf("\n--- Doubly Linked List Menu ---\n");
        printf("1.Insert Begin\n2.Insert End\n3.Insert Position\n");
        printf("4.Delete Begin\n5.Delete End\n6.Delete Position\n");
        printf("7.Search\n8.Display Forward\n9.Display Backward\n");
        printf("10.Count\n11.Reverse\n12.Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insertBegin(val);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                insertEnd(val);
                break;

            case 3:
                printf("Enter value and position: ");
                scanf("%d %d", &val, &pos);
                insertPos(val, pos);
                break;

            case 4:
                deleteBegin();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deletePos(pos);
                break;

            case 7:
                printf("Enter value to search: ");
                scanf("%d", &val);
                search(val);
                break;

            case 8:
                displayForward();
                break;

            case 9:
                displayBackward();
                break;

            case 10:
                countNodes();
                break;

            case 11:
                reverseList();
                printf("List reversed\n");
                break;

            case 12:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
