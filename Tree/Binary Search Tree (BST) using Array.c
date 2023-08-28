#include <stdio.h>

#define MAX_SIZE 1024
#define EMPTY -1
#define isValidIndex(i) (i >= 0 && i < MAX_SIZE)
#define getLeftChildIndex(i) (2 * i + 1)
#define getRightChildIndex(i) (2 * i + 2)

void init (int bst[]);
void insertNode (int bst[], int data);
int searchNode (int bst[], int target);
void deleteNode (int bst[], int target);
void deleteSingleParent (int bst[], int targetIndex);
void deleteParentOfTwo(int bst[], int targetIndex);
int getMin (int bst[], int index);
void preorderTraversal (int binaryTree[], int index);
void inorderTraversal (int binaryTree[],  int index);
void postorderTraversal (int binaryTree[], int index);


int main ()
{
    int bst[MAX_SIZE];
    int data, option;

    init(bst);

    do
    {
        printf("\n** MENU **\n");
        printf("1. Insert node\n");
        printf("2. Delete node\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);
        
        switch (option)
        {
            case 1:
            	printf("Enter an element to insert: ");
            	scanf("%d", &data);
            	insertNode(bst, data);
            	printf("%d successfully inserted.\n", data);
            	break;
            case 2:
            	printf("Enter an element to delete: ");
            	scanf("%d", &data);
            	deleteNode(bst, data);
            	break;
            case 3:
                printf("Inorder traversed elements are below:\n");
                inorderTraversal(bst, 0);
                break;
            case 4:
                printf("Preorder traversed elements are below:\n");
                preorderTraversal(bst, 0);
                break;
            case 5:
                printf("Postorder traversed elements are below:\n");
                postorderTraversal(bst, 0);
                break;
            case 6:
                printf("Program exited.\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }
    } while (option != 5);
    return 0;
}
void init (int bst[])
{
    int i;
    for (i = 0; isValidIndex(i); i++)
    {
        bst[i] = EMPTY;
    }
}

void insertNode (int bst[], int data) // inserts a node, no duplicate element allowed
{
	int index = 0;
	while (isValidIndex(index))
	{
		if (bst[index] == data) // dont insert if it already exists
			return;
		if (bst[index] == EMPTY) // only insert if the node is empty
		{
			bst[index] = data;
			return;
		}
		else if (data < bst[index]) // if data is less than current node's data, it should be placed in the right side
			index = getLeftChildIndex(index);
		else // if data is greater than current node's value, it should be placed on the right side
			index = getRightChildIndex(index);
	}
	// we reach here if index is out of bound
	fprintf(stderr, "Error: Not enough space.");
}

int searchNode (int bst[], int target)
{
	int index=0;
	while (isValidIndex(index))
	{
		if (bst[index] == EMPTY)
			return EOF;
		if (bst[index] == target)
			return index;
		else if (target < bst[index])
			index = getLeftChildIndex(index);
		else
			index = getRightChildIndex(index);
	}
	return EOF; // return EOF to indicate that element has not been found
}

void deleteNode (int bst[], int target)
{
	int left, right;
	int loc = searchNode(bst, target);
	if (loc == EOF)
	{
		printf("Node not found. Could not be deleted.\n");
		return;
	}
	left = getLeftChildIndex(loc);
	right = getRightChildIndex(loc);
	if (bst[left] != EMPTY && bst[right] != EMPTY)
		deleteParentOfTwo(bst, loc);
	else
		deleteSingleParent(bst, loc);
	printf("%d successfully deleted.\n", target);
}


void deleteSingleParent (int bst[], int targetIndex)
{
	int left, right;
	if (!isValidIndex(targetIndex))
		return;
	left = getLeftChildIndex(targetIndex);
	right = getRightChildIndex(targetIndex);
	if (!isValidIndex(left) || !isValidIndex(right) || (bst[left] == EMPTY && bst[right] == EMPTY)) // for no child case
	{
		bst[targetIndex] = EMPTY;
		return;
	}
	if (bst[left] != EMPTY && bst[right] == EMPTY) // for only left child
	{
		bst[targetIndex] = bst[left];
		bst[left] = EMPTY;
		return;
	}
	if (bst[left] == EMPTY && bst[right] != EMPTY) // for only right child
	{
		bst[targetIndex] = bst[right];
		bst[right] = EMPTY;
		return;
	}
}

void deleteParentOfTwo(int bst[], int targetIndex)
{
	int successor, successorIndex;
	if (!isValidIndex(targetIndex))
		return;
	successorIndex = getMin(bst, getRightChildIndex(targetIndex)); // find the inorder successor
	successor = bst[successorIndex];
	deleteSingleParent(bst, successorIndex);
	bst[targetIndex] = successor;
}


int getMin (int bst[], int index)
{
    while (isValidIndex(getLeftChildIndex(index)) && bst[getLeftChildIndex(index)] != EMPTY)
    {
        index = getLeftChildIndex(index);
    }
    return index;
}


void preorderTraversal (int binaryTree[], int index)
{
    if (isValidIndex(index) && binaryTree[index] != EMPTY)
    {
        printf("%d, ", binaryTree[index]);
        preorderTraversal(binaryTree, 2 * index + 1); // for left child
        preorderTraversal(binaryTree, 2 * index + 2); // for right child
    }
}

void inorderTraversal (int binaryTree[],  int index)
{
    if (isValidIndex(index) && binaryTree[index] != EMPTY)
    {
        inorderTraversal(binaryTree, 2 * index + 1); // for left child
        printf("%d, ", binaryTree[index]);
        inorderTraversal(binaryTree, 2 * index + 2); // for right child
    }
}

void postorderTraversal (int binaryTree[], int index)
{
    if (isValidIndex(index) && binaryTree[index] != EMPTY)
    {
        postorderTraversal(binaryTree, 2 * index + 1); // for left child
        postorderTraversal(binaryTree, 2 * index + 2); // for right child
        printf("%d, ", binaryTree[index]);
    }
}
