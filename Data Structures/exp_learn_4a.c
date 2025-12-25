#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    struct Node* Llink;
    int data;
    struct Node* Rlink;
}*Node;

Node Create_Node(int data){
    Node NN = malloc(sizeof(struct Node));
    if (NN == NULL){
        printf("No Memory Allocated!!\n");
        exit(1);
    }
    NN -> data = data;
    NN -> Llink = NULL;
    NN -> Rlink = NULL;
    return NN;
}

Node Insert_Front(Node Head, int data){
    Node NN = Create_Node(data);
    if (Head == NULL){
        return NN;
    }
    Head -> Llink = NN;
    NN -> Rlink = Head;
    Head = Head -> Llink;
    return NN;
}

void display(Node Head){
    if (Head == NULL){
        printf("No Data Present.!\n");
    }
    else {
        Node t = Head;
        while(t != NULL){
            printf("%d <==> ",t -> data);
            t = t -> Rlink;
        }
        printf("NULL\n");
    }
}

Node Insert_Rear(Node Head, int data){
    Node NN = Create_Node(data);
    if(Head == NULL){
        return NN;
    }
    Node curr = Head;
    while(curr -> Rlink != NULL){
        curr = curr -> Rlink;
    }
    curr -> Rlink = NN;
    curr -> Rlink -> Llink = curr;
    return Head;
}

Node Delete_Front(Node Head){
    if(Head == NULL){
        printf("No data present");
        return NULL;
    }
    if (Head -> Rlink == NULL){
        free(Head);
        return NULL;
    }
    Head = Head -> Rlink;
    free(Head -> Llink);
    Head -> Llink = NULL;
    return Head;
}

Node Delete_Rear(Node Head){
    if(Head == NULL){
        printf("No data present");
        return NULL;
    }
    if (Head -> Rlink == NULL){
        free(Head);
        return NULL;
    }
    Node curr = Head;
    while(curr -> Rlink -> Rlink != NULL){
        curr = curr -> Rlink;
    }
    free(curr->Rlink);
    curr -> Rlink = NULL;
    return Head;
}

void Count_Nodes(Node Head){
    if(Head == NULL){
        printf("The Number of nodes is 0.\n");
    }
    Node t = Head;
    int count = 0;
    while(t != NULL){
        count++;
        t = t -> Rlink;
    }
    printf("The Number of nodes present are %d.\n",count);
}

int main(void){
    Node h = NULL;

    int choice; 
    printf("--------------------- Doubly Linked List(DLL) operations ---------------------\n\n");
    printf("Insert at front           - 1\n");
    printf("Insert at Rear            - 2\n");
    printf("Delete at front           - 3\n");
    printf("Delete at Rear            - 4\n");
    printf("Count the number of nodes - 5\n");
    printf("Display                   - 6\n");
    printf("Exit                      - 0\n\n");
    
    while(choice != 0){
        printf("Enter your choice: ");
        scanf("%d",&choice);
        
        int num1;
        if (choice == 1) {
            printf("Enter the element/data that you want to insert at front: ");
            scanf("%d",&num1);
        }
        if (choice == 2)
        {
            printf("Enter the element/data that you want to insert at rear: ");
            scanf("%d",&num1);
        }
        
    switch (choice){
        case 1:
            h = Insert_Front(h, num1);
            printf("Element inserted\n");
            break;
        case 2:
            h = Insert_Rear(h, num1);
            printf("Element inserted\n");
            break;
        case 3:
            h = Delete_Front(h);
            printf("Element deleted\n");
            break;
        case 4:
            h = Delete_Rear(h);
            printf("Element deleted\n");
            break;
        case 5:
            Count_Nodes(h);
            break;
        case 6:
            display(h);
            break;
        case 0:
            printf("Exit\n");
            break;
        default:
            printf("Invalid Choice\n");
            break;
    }
    }
    return 0;
}