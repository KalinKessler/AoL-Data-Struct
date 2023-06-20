#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node* left;
    struct node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(struct node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct node* createNode(int key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct node* insert(struct node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && key < node->left->key)
        return rightRotate(node);

    if (balanceFactor < -1 && key > node->right->key)
        return leftRotate(node);

    if (balanceFactor > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct node* findMinValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct node* temp = findMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(struct node* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->key);
    inorderTraversal(root->right);
}

void preorderTraversal(struct node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->key);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct node* root) {
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->key);
}

int main() {
    struct node* root = NULL;
    int menu, data;

    do {
        system("cls");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("Insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Data inserted successfully.\n");
                system("pause");
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Data deleted successfully.\n");
                system("pause");
                break;
            case 3:
                printf("Preorder: ");
                preorderTraversal(root);
                printf("\n");
                printf("Inorder: ");
                inorderTraversal(root);
                printf("\n");
                printf("Postorder: ");
                postorderTraversal(root);
                printf("\n");
                system("pause");
                break;
            case 4:
                system("cls");
                printf("Thank you.\n");
                system("pause");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                system("pause");
                break;
        }
        printf("\n");
    } while (menu != 4);

    return 0;
}
