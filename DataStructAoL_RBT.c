#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int data;
    enum Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* bstInsert(struct Node* root, struct Node* newNode) {
    if (root == NULL) {
        return newNode;
    } else if (newNode->data < root->data) {
        root->left = bstInsert(root->left, newNode);
        root->left->parent = root;
    } else if (newNode->data > root->data) {
        root->right = bstInsert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void fixViolation(struct Node** root, struct Node* newNode) {
    while (newNode != *root && newNode->parent->color == RED) {
        struct Node* parent = newNode->parent;
        struct Node* grandparent = newNode->parent->parent;

        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->right) {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rightRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        } else {
            struct Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->left) {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                leftRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        }
    }
    (*root)->color = BLACK;
}

void insert(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    *root = bstInsert(*root, newNode);
    fixViolation(root, newNode);
}

void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    insert(&root, 41);
    insert(&root, 22);
    insert(&root, 5);
    insert(&root, 51);
    insert(&root, 48);
    insert(&root, 29);
    insert(&root, 18);
    insert(&root, 21);
    insert(&root, 45);
    insert(&root, 3);

    printf("In-order Traversal Of Created Tree: \n");
    inOrderTraversal(root);

    return 0;
}

