#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int data;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode *ROOT, *NIL;

void initializeRBT() {
    NIL = (RBNode *)malloc(sizeof(RBNode));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;
    ROOT = NIL;
}

RBNode* createNode(int data) {
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

void leftRotate(RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        ROOT = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        ROOT = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* ---------- INSERT FIXUP ---------- */
void insertFixup(RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *uncle = z->parent->parent->right;

            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            RBNode *uncle = z->parent->parent->left;

            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    ROOT->color = BLACK;
}

/* ---------- INSERT ---------- */
void insert(int data) {
    RBNode *z = createNode(data);
    RBNode *y = NIL;
    RBNode *x = ROOT;

    while (x != NIL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NIL)
        ROOT = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(z);
}

/* ---------- SEARCH ---------- */
RBNode* search(RBNode *root, int key) {
    if (root == NIL || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

/* ---------- TRANSPLANT ---------- */
void transplant(RBNode *u, RBNode *v) {
    if (u->parent == NIL)
        ROOT = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

RBNode* minimum(RBNode *node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

/* ---------- DELETE FIXUP ---------- */
void deleteFixup(RBNode *x) {
    while (x != ROOT && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = ROOT;
            }
        } else {
            RBNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = ROOT;
            }
        }
    }
    x->color = BLACK;
}


void deleteNode(int key) {
    RBNode *z = search(ROOT, key);
    if (z == NIL) return;

    RBNode *y = z;
    Color yOriginalColor = y->color;
    RBNode *x;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK)
        deleteFixup(x);

    free(z);
}

void inorder(RBNode *root) {
    if (root != NIL) {
        inorder(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorder(root->right);
    }
}

void printTreeASCII(RBNode *root, int space) {
    if (root == NIL)
        return;

    space += 6;

    printTreeASCII(root->right, space);

    printf("\n");
    for (int i = 6; i < space; i++)
        printf(" ");

    printf("|-- %d(%s)\n", root->data,
           root->color == RED ? "R" : "B");

    printTreeASCII(root->left, space);
}

/* ---------- MAIN ---------- */
int main() {
    initializeRBT();

    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(80);
    insert(35);
    insert(75);
    insert(32);
    insert(56);
    insert(17);

    // inorder(ROOT);
    printTreeASCII(ROOT, 0);
    printf("\n----------------------\n");
    
    deleteNode(20);
    printTreeASCII(ROOT, 0);

    return 0;
}