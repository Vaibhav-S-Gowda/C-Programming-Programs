#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* Llink;
    int data;
    struct node* Rlink;
} *Node;

Node create_node(int data) {
    Node NN = malloc(sizeof(struct node));
    if(NN == NULL) {
        printf("No memory allocated\n");
        exit(1);
    }
    NN->Llink = NN->Rlink = NULL;
    NN->data = data;
    return NN;
}

Node create_head() {
    Node head = malloc(sizeof(struct node));
    if(head == NULL) {
        printf("No memory allocated\n");
        exit(1);
    }
    head->Llink = head->Rlink = head;
    head->data = -1;
    return head;
}

Node insert_front(Node head, int data) {
    Node NN = create_node(data);
    NN->Rlink = head->Rlink; // New node points to first node
    NN->Llink = head;        // New node's left points to head
    head->Rlink->Llink = NN; // Old first node's left points to new node
    head->Rlink = NN;        // Head's right now points to new node
    return head;
}

Node insert_rear(Node head, int data) {
    Node NN = create_node(data);
    NN->Rlink = head;
    NN->Llink = head->Llink;
    NN->Llink->Rlink = NN;
    head->Llink = NN;
    return head;
}

void display(Node head) {
    if (head->Rlink == head) {
        printf("List is empty.\n");
        return;
    }
    Node temp = head->Rlink;
    printf("Head ");
    while (temp != head) {
        printf("<=> %d ", temp->data);
        temp = temp->Rlink;
    }
    printf("<=> Head\n");
}

Node delete_front(Node head) {
    head = head->Rlink;
    head->Llink = (head->Llink)->Llink;
    free((head->Llink)->Rlink);
    (head->Llink)->Rlink = head;
    return head;
}

Node delete_rear(Node head) {
    head->Llink = (head->Llink)->Llink;
    free((head->Llink)->Rlink);
    ((head->Llink)->Rlink) = head;
    return head;
}

void display_reverse(Node head) {
    if (head->Llink == head) {
        printf("List is empty.\n");
        return;
    }
    Node temp = head->Llink;
    printf("Head ");
    while (temp != head) {
        printf("<=> %d ", temp->data);
        temp = temp->Llink;
    }
    printf("<=> Head\n");
}

void search_ticket(Node head, int key) {
    if (head->Rlink == head) {
        printf("List is empty\n");
        return;
    }
    Node temp = head->Rlink;
    int pos = 1;
    while (temp != head) {
        if (temp->data == key) {
            printf("Ticket %d found at position %d\n", key, pos);
            return;
        }
        temp = temp->Rlink;
        pos++;
    }
    printf("Ticket %d not found in the list\n", key);
}

int main(void) {
    Node h = create_head();
    
    int choice;
    printf("1. Insert at Front.\n");
    printf("2. Insert at Rear.\n");
    printf("3. Delete at Front.\n");
    printf("4. Delete at Rear.\n");
    printf("5. Display the queue.\n");
    printf("6. Reverse the queue.\n");
    printf("7. Search the Ticket.\n");
    printf("0. Exit.\n");
    
    while (choice != 0) {
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        int num;
        if (choice == 1 || choice == 2 || choice == 7) {
            printf("Enter the element: ");
            scanf("%d",&num);
        }
        switch (choice) {
            case 1:
                h = insert_front(h, num);
                printf("Element Inserted\n");
                break;
            case 2:
                h = insert_rear(h, num);
                printf("Element Inserted\n");
                break;
            case 3:
                h = delete_front(h);
                if(h == NULL) break;
                printf("Element deleted at front\n");
                break;
            case 4:
                h = delete_rear(h);
                if(h == NULL) break;
                printf("Element deleted at Rear\n");
                break;
            case 5:
                display(h);
                break;
            case 6:
                printf("\nReversed Double Linked List:\n");
                display_reverse(h);
                break;
            case 7:
                printf("\nSearch the Ticket:\n");
                search_ticket(h, num);
                break;
        }
    }
    return 0;
}