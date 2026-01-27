#include<stdio.h>
#include<stdlib.h>

typedef struct myNode
{
    int data;
    struct myNode *left,*right;
}*NODE;

NODE newNode(int value)
{
    NODE newnode = (NODE)malloc(sizeof(struct myNode));
    if(newnode == NULL)
    {
        printf("memory not alloocated\n");
        exit(1);
    }
    newnode->data = value;
    newnode->left = newnode->right = NULL;

    return newnode;
}

NODE insert(NODE root, int value)
{
    if(root == NULL)
    {
        NODE root = newNode(value);
        return root;
    }

    if(value < root->data)
    {
        root->left = insert(root->left , value);
    }
    else
    {
        root->right = insert(root->right , value);
    }
    return root;
}

NODE findlargestnode(NODE root)
{
    while(root->right != NULL)
    {
        root = root->right;
    }
return root;
}

NODE deletenode(NODE root ,int key)
{
    if(root==NULL)
    {
        printf("Item not found");
        return root;
    }

    if(key < root->data)
        root->left = deletenode(root->left , key);
    else if(key > root->data)
        root->right = deletenode(root->right , key);

    else 
    {
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }

        else if(root->left == NULL)
        {
            NODE temp = root;
            root = root->right;
            free(temp);
        }

        else if(root->right == NULL)
        {
            NODE temp = root;
            root = root->left;
            free(temp);
        }

    else{
        NODE temp = findlargestnode(root->left);
        root->data = temp->data;
        root->left = deletenode(root->left , temp->data);
    }
    }
    return root;
}

NODE searchnode(NODE root ,int key)
{
    if(root==NULL || root->data == key)
    {
        return root;
    }
    return (key < root->data)?searchnode(root->left,key):searchnode(root->right,key);
}

void inorder(NODE root)
{
    if(root == NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d\n",root->data);
    inorder(root->right);
}

void freetree(NODE root)
    {
        if(root == NULL)
        {
            return;
        }
        freetree(root->left);
        freetree(root->right);
        free(root);
    }


// 
int main()
{
    NODE root = NULL;

    root = insert(root,20);
    insert(root,10);
    insert(root,30);
    insert(root,5);
    insert(root,15);
    insert(root,25);
    insert(root,35);

    printf("Inorder\n");
    inorder(root);

    printf("\nSearch\n");
    int key = 10;

    NODE found = searchnode(root,key);   

    if(found)
        printf("%d found in tree\n",key);
    else
        printf("key not found\n");

    printf("\nDelete\n");
    root = deletenode(root,10);

    printf("Inorder\n");
    inorder(root);

    freetree(root);

    return 0;
}