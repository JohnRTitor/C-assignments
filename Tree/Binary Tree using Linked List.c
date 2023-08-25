#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int info;
	struct node *left;
	struct node *right;
} NODE;

NODE* createNode (int data)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: Memory not allocated.");
		exit(-1);
	}
	newNode->info = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void inorderTraversal (NODE *root)
{
	if (root != NULL)
	{
		inorderTraversal(root->left);
		printf("%d, ", root->info);
		inorderTraversal(root->right);
	}
}

void preorderTraversal (NODE *root)
{
	if (root != NULL)
	{
		printf("%d, ", root->info);
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

void postorderTraversal (NODE *root)
{
	if (root != NULL)
	{
		postorderTraversal(root->left);
		postorderTraversal(root->right);
		printf("%d, ", root->info);
	}
}

NODE* createTree ()
{
	NODE *root;
	int data;
	printf("(enter %d to not insert any node) ", -1);
	scanf("%d", &data);
	if (data == -1)
		return NULL;
	root = createNode(data);
	printf("Enter left child of %d: ", data);
	root->left = createTree(); // run the createTree function recursively to get the left child
	printf("Enter the right child of %d: ", data);
	root->right = createTree();
	return root;
}

void freeTree (NODE **root)
{
    if (*root != NULL)
    {
        freeTree( &((*root)->left) );
        freeTree( &((*root)->right) );
        free(*root);
        *root = NULL;
    }
}

int main()
{
    int option;
	NODE *root;
	printf("Enter the root element:");
	root = createTree();
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
                inorderTraversal(root);
                break;
            case 2:
                printf("Preorder traversed elements are below:\n");
                preorderTraversal(root);
                break;
            case 3:
                printf("Postorder traversed elements are below:\n");
                postorderTraversal(root);
                break;
            case 4:
                printf("Please recreate the tree:\n");
                printf("Enter the root element: ");
                freeTree(&root);
                root = createTree();
                break;
            case 5:
                printf("Program exited.\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }
    } while (option != 5);
    freeTree(&root);
	return 0;
}