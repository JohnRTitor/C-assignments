#include <stdio.h>

#define MAX_SIZE 100

void init (int binaryTree[])
{
    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        binaryTree[i] = -1;
    }
}

void insertNode (int binaryTree[], int index, int data)
{
    if (index >= MAX_SIZE)
    {
        fprintf(stderr, "Error: Binary Tree is full.");
        return;
    }
    binaryTree[index] = data;
}

void createBinaryTree (int binaryTree[], int index)
{
    int data;
    if (index == 0)
        printf("Enter data of root:");
    printf("(enter -1 to not insert any node)");
    scanf("%d", &data);
    if (data == -1)
        return;
    insertNode(binaryTree, index, data);
    printf("Enter left child of %d:", data);
    createBinaryTree(binaryTree, 2 * index + 1);
    printf("Enter right child of %d:", data);
    createBinaryTree(binaryTree, 2 * index + 2);
}

void preorderTraversal (int binaryTree[], int index)
{
    if (index < MAX_SIZE && binaryTree[index] != -1)
    {
        printf("%d, ", binaryTree[index]);
        preorderTraversal(binaryTree, 2 * index + 1); // for left child
        preorderTraversal(binaryTree, 2 * index + 2); // for right child
    }
}

void inorderTraversal (int binaryTree[],  int index)
{
    if (index < MAX_SIZE && binaryTree[index] != -1)
    {
        inorderTraversal(binaryTree, 2 * index + 1); // for left child
        printf("%d, ", binaryTree[index]);
        inorderTraversal(binaryTree, 2 * index + 2); // for right child
    }
}

void postorderTraversal (int binaryTree[], int index)
{
    if (index < MAX_SIZE && binaryTree[index] != -1)
    {
        postorderTraversal(binaryTree, 2 * index + 1); // for left child
        postorderTraversal(binaryTree, 2 * index + 2); // for right child
        printf("%d, ", binaryTree[index]);
    }
}

int main ()
{
    int binaryTree[MAX_SIZE];
    int option;

    init(binaryTree);
    createBinaryTree(binaryTree, 0);
    do
    {
        printf("\n** MENU **\n");
        printf("1. Inorder Traversal\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Recreate the binary tree:\n");
        printf("5. Exit\n");
        printf("Enter an option:\n");
        scanf("%d", &option);
        
        switch (option)
        {
            case 1:
                printf("Inorder traversed elements are below:\n");
                inorderTraversal(binaryTree, 0);
                break;
            case 2:
                printf("Preorder traversed elements are below:\n");
                preorderTraversal(binaryTree, 0);
                break;
            case 3:
                printf("Postorder traversed elements are below:\n");
                postorderTraversal(binaryTree, 0);
                break;
            case 4:
                printf("Please recreate the tree:\n");
                init(binaryTree);
                createBinaryTree(binaryTree, 0);
                break;
            case 5:
                printf("Program exited.\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }
    } while (option != 5);
    return 0;
}