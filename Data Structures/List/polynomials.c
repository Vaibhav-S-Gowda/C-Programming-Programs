#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int coeff;
    int power;
    struct Node* link;
}*Node;

Node Create_Node(int coeff,int power){
    Node NN = malloc(sizeof(struct Node));
    if(NN == NULL){
        printf("No memory allocated.\n");
        exit(1);
    }
    NN -> coeff = coeff;
    NN -> power = power;
    NN -> link = NULL;
    return NN;
}

Node Insert_Node(int coeff,int power,Node Head){
    Node NN = Create_Node(coeff,power);
    
    if(Head == NULL || power > Head -> power){
        NN -> link = Head;
        return NN;
    }
    
    Node temp = Head;
    Node prev = NULL;
    while((temp != NULL) && (temp -> power > power)){
        prev = temp;
        temp = temp -> link;
    }
    
    if(temp != NULL && temp -> power == power){
        temp -> coeff += coeff;
        free(NN);
        return Head;
    }
    prev -> link = NN;
    NN -> link = temp;
    return Head;
}

void Display(Node Head){
    if(Head == NULL) {
        return;
    }
    Node temp = Head;
    while(temp != NULL){
        if(temp -> link == NULL){
            printf("{%d x^%d}",temp -> coeff,temp -> power);
        } else {
            printf("{%d x^%d} -> ",temp -> coeff,temp -> power);
        }
        temp = temp -> link;
    }
    printf("\n");
}

Node Add_Poly(Node head1, Node head2){
    Node result = NULL;
    
    while(head1 != NULL && head2 != NULL) {
        if(head1 -> power == head2 -> power) {
            result = Insert_Node(head1 -> coeff + head2 -> coeff, head1 -> power, result);
            head1 = head1 -> link;
            head2 = head2 -> link;
        }
        else if (head1 -> power > head2 -> power) {
            result = Insert_Node(head1 -> coeff, head1 -> power, result);
            head1 = head1 -> link;
        }
        else {
            result = Insert_Node(head2 -> coeff, head2 -> power, result);
            head2 = head2 -> link;
        }
    }
    
    while (head1 != NULL){
        result = Insert_Node(head1 -> coeff, head1 -> power, result);
        head1 = head1 -> link;
    }
    
    while (head2 != NULL){
        result = Insert_Node(head2 -> coeff, head2 -> power, result);
        head2 = head2 -> link;
    }
    return result;
}

int main(){
    Node head1 = NULL, head2 = NULL, result = NULL;
    
    head1 = Insert_Node(12, 2, head1);
    head1 = Insert_Node(8, 0, head1);
    head1 = Insert_Node(5, 1, head1);
    
    head2 = Insert_Node(6, 0, head2);
    head2 = Insert_Node(2, 2, head2);
    head2 = Insert_Node(4, 1, head2);
    
    printf("Polynomial 1: ");
    Display(head1);
    
    printf("\nPolynomial 2: ");
    Display(head2);
    
    result = Add_Poly(head1, head2);
    
    printf("\nResultant Polynomial (Sum): ");
    Display(result);
    
    return 0;
}