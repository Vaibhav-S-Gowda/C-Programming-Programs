#include<stdio.h>
#include<stdlib.h>

typedef struct myNode{
    int data;
    struct myNode* link;
}*Node;

Node Create_Node(int data){
    Node newNode = malloc(sizeof(struct myNode));
    if(newNode == NULL){
        printf("No memory allocated\n");
        exit(1);
    }
    newNode -> data = data;
    newNode -> link = NULL;
    return newNode;
}

Node Insert_at_Front(Node Header, int data){
    Node newNode = Create_Node(data);
    newNode -> link = Header;
    return newNode;
}

Node Insert_Rear(Node Head, int data){
    Node NN = Create_Node(data);
    if (Head == NULL)
    {
        return NN;
    }
    Node temp = Head;
    while(temp != NULL){
        temp = temp -> link;
    }
    temp -> link = NN;
    return Head;
}

void Display(Node Header){
    if (Header == NULL)
    {
        printf("Empty List\n");
    }
    else
    {
        Node temp = Header;
        while (temp != NULL)
        {
            printf(" %d = %p -->",temp -> data, temp -> link);
            temp = temp -> link;
        }
        printf("\n");
    }
}

int main(){
    Node head = NULL;
    Display(head);
    head = Insert_at_Front(head, 45);
    head = Insert_at_Front(head, 50);
    head = Insert_at_Front(head, 55);
    head = Insert_at_Front(head, 60);
    head = Insert_at_Front(head, 65);
    Display(head);
    head = Insert_Rear(head, 10);
    head = Insert_Rear(head, 20);
    Display(head);
    return 0;
}