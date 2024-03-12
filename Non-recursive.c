#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct StackNode {
    struct TreeNode *treeNode;
    struct StackNode *next;
};

struct Stack {
    struct StackNode *top;
};

struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void initializeStack(struct Stack *stack) {
    stack->top = NULL;
}

int isEmpty(struct Stack *stack) {
    return stack->top == NULL;
}

void push(struct Stack *stack, struct TreeNode *treeNode) {
    struct StackNode *newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->treeNode = treeNode;
    newNode->next = stack->top;
    stack->top = newNode;
}

struct TreeNode* pop(struct Stack *stack) {
    if (isEmpty(stack)) return NULL;
    struct TreeNode *poppedNode = stack->top->treeNode;
    struct StackNode *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return poppedNode;
}

void preOrderTraversal(struct TreeNode *root) {
    if (root == NULL) return;

    struct Stack stack;
    initializeStack(&stack);
    push(&stack, root);

    while (!isEmpty(&stack)) {
        struct TreeNode *currentNode = pop(&stack);
        printf("%d ", currentNode->data);

        if (currentNode->right != NULL) {
            push(&stack, currentNode->right);
        }
        if (currentNode->left != NULL) {
            push(&stack, currentNode->left);
        }
    }
}

void inOrderTraversal(struct TreeNode *root) {
    if (root == NULL) return;

    struct Stack stack;
    initializeStack(&stack);
    struct TreeNode *currentNode = root;

    while (currentNode != NULL || !isEmpty(&stack)) {
        while (currentNode != NULL) {
            push(&stack, currentNode);
            currentNode = currentNode->left;
        }

        currentNode = pop(&stack);
        printf("%d ", currentNode->data);

        currentNode = currentNode->right;
    }
}

void postOrderTraversal(struct TreeNode *root) {
    if (root == NULL) return;

    struct Stack stack;
    initializeStack(&stack);
    struct TreeNode *currentNode = root;
    struct TreeNode *lastVisitedNode = NULL;

    while (currentNode != NULL || !isEmpty(&stack)) {
        while (currentNode != NULL) {
            push(&stack, currentNode);
            currentNode = currentNode->left;
        }

        struct TreeNode *peekNode = stack.top->treeNode;

        if (peekNode->right != NULL && peekNode->right != lastVisitedNode) {
            currentNode = peekNode->right;
        } else {
            printf("%d ", peekNode->data);
            lastVisitedNode = pop(&stack);
        }
    }
}

int main() {
    struct TreeNode *root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("Pre-order traversal: ");
    preOrderTraversal(root);
    printf("\n");

    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    return 0;
}
