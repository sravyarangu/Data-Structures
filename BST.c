//BST
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *right;
    struct node *left;
} *root = NULL;

int val, key;

void create();
void insert(struct node*, struct node*);
struct node* delete_node(struct node*, int);
struct node* search(struct node*, int);
void inorder(struct node*);
void postorder(struct node*);
void preorder(struct node*);
struct node* find_min(struct node*);

void create() {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->left = NULL;
    new_node->right = NULL;

    printf("Enter value: ");
    scanf("%d", &val);
    new_node->data = val;

    if (root == NULL) {
        root = new_node;
    } else {
        insert(root, new_node);
    }
}

struct node* find_min(struct node* root) {
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;
    else
        return find_min(root->left);
}

void insert(struct node* root, struct node* new_node) {
    if (new_node->data < root->data) {
        if (root->left == NULL) {
            root->left = new_node;
        } else {
            insert(root->left, new_node);
        }
    } else {
        if (root->right == NULL) {
            root->right = new_node;
        } else {
            insert(root->right, new_node);
        }
    }
}

struct node* delete_node(struct node* root, int val) {
    if (root == NULL)
        return root;

    if (val < root->data) {
        root->left = delete_node(root->left, val);
    } else if (val > root->data) {
        root->right = delete_node(root->right, val);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            struct node *temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            struct node *temp = root;
            root = root->left;
            free(temp);
        } else {
            struct node *temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }
    return root;
}

void inorder(struct node* temp) {
    if (temp != NULL) {
        inorder(temp->left);
        printf("%d ", temp->data);
        inorder(temp->right);
    }
}

void postorder(struct node* temp) {
    if (temp != NULL) {
        postorder(temp->left);
        postorder(temp->right);
        printf("%d ", temp->data);
    }
}

void preorder(struct node* temp) {
    if (temp != NULL) {
        printf("%d ", temp->data);
        preorder(temp->left);
        preorder(temp->right);
    }
}

struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Create\n2. Insert\n3. Delete\n4. Search\n5. Inorder\n6. Postorder\n7. Preorder\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                // Note: insert is called within create, so no need to call it separately
                printf("Create a node first using option 1.\n");
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = delete_node(root, val);
                break;
            case 4:
                printf("Enter value to search: ");
                scanf("%d", &key);
                if (search(root, key) != NULL)
                    printf("Value found\n");
                else
                    printf("Value not found\n");
                break;
            case 5:
                inorder(root);
                printf("\n");
                break;
            case 6:
                postorder(root);
                printf("\n");
                break;
            case 7:
                preorder(root);
                printf("\n");
                break;
            case 8:
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
