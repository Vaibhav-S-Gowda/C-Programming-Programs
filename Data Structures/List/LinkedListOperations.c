#include<stdio.h>
#include<stdlib.h>

typedef struct mynode{
    int data;
    struct mynode *link;
}*NODE;

NODE Create_Node(int data){
    NODE newNode = malloc(sizeof(struct mynode));
    if(newNode == NULL){
        printf("Memory is not allocated!!");
        exit(1);
    }
    newNode -> data = data;
    newNode -> link = NULL;
    return newNode;
}

NODE Insert_Front(NODE Header, int data){
    NODE newNode = Create_Node(data);
    newNode -> link = Header;
    return newNode;
}

void Display_Node(NODE Header){
    if (Header == NULL){
        printf("Empty List\n");
        return;
    }
    else{
        NODE temp = Header;
        while(temp != NULL){
            if(temp -> link == NULL){
                printf(" %d",temp -> data);
            }
            else{
            printf(" %d ->",temp -> data);
            }
            temp = temp -> link;
        }
        printf("\n");
    }
}

NODE Insert_Rear(NODE Header, int data){
    NODE newNode = Create_Node(data);
    if(Header == NULL){
        return newNode;
    }
    NODE temp = Header;
    while(temp->link != NULL){
        temp = temp -> link;
    }
    temp -> link = newNode;
    return Header;
}

NODE Insert_Pos(NODE Header, int data, int pos){
    if((Header == NULL) || (pos <= 0)){
        return Insert_Front(Header,data);
    }
    NODE curr = Header;
    int currentPos = 1;
    while((curr != NULL) && (currentPos < (pos - 1))){
        curr = curr -> link;
        currentPos++;
    }
    if(curr == NULL)
    {
        printf("Position > Number of Node\t");
        printf("Insert at End\n");
        return(Insert_Rear(Header, data));
    }
    NODE newNode = Create_Node(data);
    newNode -> link = curr -> link;
    curr -> link = newNode;
    return Header;
}

NODE Delete_Front(NODE Header){
    if(Header == NULL){
        printf("Empty list");
    }
    else{
        NODE temp = Header;
        Header = Header -> link;
        free(temp);
    }
    return Header;
}

NODE Delete_Rear(NODE Header){
    if(Header == NULL){
        printf("Empty Node");
    }
    else{
        NODE temp = Header;
        NODE prev = NULL;
        while(temp -> link != NULL){
            prev = temp;
            temp = temp -> link;
        }
        prev -> link = NULL;
        free(temp);
        return Header;
    }
}

int main(){
    printf("-----Linked List Opertions-----\n");
    NODE node = NULL;
    printf("Insert at Front Operations \n");
    node = Insert_Front(node, 68);
    node = Insert_Front(node, 28);
    node = Insert_Front(node, 32);
    node = Insert_Front(node, 11);
    node = Insert_Front(node, 6);
    Display_Node(node);

    printf("Insert at Rear Operations \n");
    node = Insert_Rear(node, 50);
    node = Insert_Rear(node, 60);
    Display_Node(node);

    printf("Insert at Position Operations \n");
    node = Insert_Pos(node, 15, 5);
    node = Insert_Pos(node, 5, 7);
    node = Insert_Pos(node, 100, 0);
    Display_Node(node);

    printf("Delete at Front Operations \n");
    node = Delete_Front(node);
    node = Delete_Front(node);
    Display_Node(node);

    printf("Delete at Rear Operations \n");
    node = Delete_Rear(node);
    node = Delete_Rear(node);
    Display_Node(node);
    return 0;
}

/*

    | Operation       | Time Complexity |
    | --------------- | --------------- |
    | Create Node     | O(1)            |
    | Insert Front    | O(1)            |
    | Insert Rear     | O(n)            |
    | Insert Position | O(n)            |
    | Display         | O(n)            |
    | Delete Front    | O(1)            |
    | Delete Rear     | O(n)            |

*/


/*
    Output:

    -----Linked List Opertions-----
    Insert at Front Operations 
    6 -> 11 -> 32 -> 28 -> 68
    Insert at Rear Operations 
    6 -> 11 -> 32 -> 28 -> 68 -> 50 -> 60
    Insert at Position Operations 
    100 -> 6 -> 11 -> 32 -> 28 -> 15 -> 68 -> 5 -> 50 -> 60
    Delete at Front Operations 
    11 -> 32 -> 28 -> 15 -> 68 -> 5 -> 50 -> 60
    Delete at Rear Operations 
    11 -> 32 -> 28 -> 15 -> 68 -> 5
*/