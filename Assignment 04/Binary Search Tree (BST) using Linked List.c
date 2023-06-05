#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#pragma GCC diagnostic ignored "-Wgnu-statement-expression"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#define IS_INVALID_OPTION(x) (x == 1 || x == 2 || x == 8 || x == 9 || x == 10)
#define IS_EMPTY(root) \
	({\
		if (root == NULL)\
		{\
			fprintf(stderr, "Error: Tree is empty.");\
			break;\
		}\
	})

typedef struct node
{
	int info;
	struct node *left;
	struct node *right;
} NODE;

typedef struct stackNode
{
	NODE *treeNode;
	struct stackNode *link;
} SNODE;

NODE* createNode (int data);
int isBST(NODE* root);
int isBSTUtil (NODE *root, int minVal, int maxVal);

void inorderTraversal (NODE *root, int recursion);
void inorderRecursive (NODE *root);
void inorderIterative (NODE *root);

void preorderTraversal (NODE *root, int recursion);
void preorderRecursive (NODE *root);
void preorderIterative (NODE *root);

void postorderTraversal (NODE *root, int recursion);
void postorderRecursive (NODE *root);
void postorderIterative (NODE *root);

void levelOrderTraversal (NODE *root);
void printCurrentLevel (NODE *root, int level);

int getHeight (NODE *root);
NODE* findMin (NODE *root);
NODE* findMax (NODE *root);
int countLeafNodes (NODE *root);
int countNonLeafNodes (NODE *root);
void searchNode (NODE *root, int target, NODE **par, NODE **loc);

void insertNode(NODE **root, int recursion);
NODE* insertNodeRecursive (NODE *root, int data);
void insertNodeIterative (NODE **root, int data);

void deleteNode(NODE **root, int recursion);
NODE* deleteNodeRecursive (NODE *root, int data);
void deleteNodeIterative (NODE **root, int target);
void deleteParentOfTwo (NODE **root, NODE **par, NODE **loc);
void deleteSingleParent (NODE **root, NODE **par, NODE **loc);

void mirrorTree (NODE *root);
void freeTree (NODE **root);
void push (SNODE **top, NODE *tNode);
NODE* pop (SNODE **top);NODE* peek (SNODE *top);int isStackEmpty(SNODE *top);
void clearBuffer (void);

int main()
{
	int recursion = true;
	char mode[11] = "recursion";
	NODE *root = NULL;
    int data, option, BST;
	NODE *loc, *par;
    do
    {
        BST = isBST(root);
        printf("\n** MENU **\n");
        printf("0. Change Mode (current: %s)\n", mode);
        if (BST)
        {
        	printf("1. Insert a node^°\n");
        	printf("2. Delete a node^°\n");
        }
        printf("3. Inorder Traversal^\n");
        printf("4. Preorder Traversal^\n");
        printf("5. Postorder Traversal^\n");
        printf("6. Level order traversal\n");
        printf("7. Find the height of the tree\n");
        if (BST)
	    {
	        printf("8. Find the minimum element°\n");
	        printf("9. Find the maximum element°\n");
	        printf("10. Search element°\n");
        }
        printf("11. Count the number of leaf nodes\n");
        printf("12. Count the number of non-leaf nodes\n");
        printf("13. Mirror tree\n");
        printf("14. Delete tree\n");
        printf("15. Exit\n");
        printf("^ - Affected by mode change.\n");
        printf("° - Maybe unavailable after mirroring.\n");
        printf("Enter an option: ");
        if (scanf("%d", &option) != 1)
        {
        	clearBuffer();
        	continue;
        }
        clearBuffer();
        if (!BST && IS_INVALID_OPTION(option)) // due to issues after mirroring, inaccessible options are to forwarded to an error message
        	option = 99;
        
        
        switch (option)
        {
        	case 0:
        		printf("Press 1 for recursive mode, or any key for iterative mode: ");
        		recursion = (getchar() == '1');
        		strcpy(mode, ((recursion) ? "recursion" : "iteration"));
        		clearBuffer();
        		break;
			case 1:
				insertNode(&root, recursion);
				IS_EMPTY(root);
				break;
			case 2:
				IS_EMPTY(root);
				deleteNode(&root, recursion);
				break;
            case 3:
                IS_EMPTY(root);
                inorderTraversal(root, recursion);
                break;
            case 4:
                IS_EMPTY(root);
                preorderTraversal(root, recursion);
                break;
            case 5:
                IS_EMPTY(root);
                postorderTraversal(root, recursion);
                break;
            case 6:
            	IS_EMPTY(root);
            	levelOrderTraversal(root);
            	break;
            case 7:
            	IS_EMPTY(root);
            	printf("Height of the tree is %d.\n", getHeight(root));
            	break;
            case 8:
            	IS_EMPTY(root);
            	loc = findMin(root);
            	printf("The minimum element of the tree is %d.\n", loc->info);
            	break;
            case 9:
            	IS_EMPTY(root);
            	loc = findMax(root);
            	printf("The maximum element of the tree is %d.\n", loc->info);
            	break;
            case 10:
            	IS_EMPTY(root);
            	printf("Which element to search?");
            	scanf("%d", &data);
            	searchNode(root, data, &loc, &par);
            	if (loc != NULL)
            		printf("%d found in the tree.\n", data);
            	else
            		printf("%d not found in the tree.\n", data);
            	clearBuffer();
            	break;
            case 11:
            	IS_EMPTY(root);
            	printf("There are %d leaf nodes in the tree.\n", countLeafNodes(root));
            	break;
            case 12:
            	IS_EMPTY(root);
            	printf("There are %d non-leaf nodes in the tree.\n", countNonLeafNodes(root));
            	break;
            case 13:
            	IS_EMPTY(root);
            	mirrorTree(root);
            	printf("Successfully mirrored the tree.\n");
            	break;
            case 14:
            	freeTree(&root);
            	printf("Successfully deleted the entire tree.\n");
            	break;
            case 15:
                printf("Program exited.\n");
                break;
            case 99:
            	printf("The tree is no longer a binary search tree (BST). If you have mirrored the tree, please mirror it again to fix it. Only a few options are available.\n");
            	break;
            default:
                printf("Invalid input. Please try again.\n");
        }
    } while (option != 15);
    freeTree(&root);
	return 0;
}

NODE* createNode (int data)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: Memory not allocated.");
		return NULL;
	}
	newNode->info = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void insertNode (NODE **root, int recursion)
{
	int data;
	printf("Enter the data to be inserted: ");
	if (scanf("%d", &data) != 1)
	{
		fprintf(stderr, "Error: Insertion failed.\n");
		clearBuffer();
		return;
	}
	if (recursion)
		*root = insertNodeRecursive(*root, data);
	else
		insertNodeIterative(root, data);
	
	printf("%d successfully inserted.\n", data);
}

void deleteNode (NODE **root, int recursion)
{
	int data;
	printf("Enter the data to be deleted: ");
	if (scanf("%d", &data) != 1)
	{
		fprintf(stderr, "Error: Deletion failed.\n");
		clearBuffer();
		return;
	}
	if (recursion)
		*root = deleteNodeRecursive(*root, data);
	else
		deleteNodeIterative(root, data);
	
	printf("%d successfully deleted.\n", data);
}

void inorderTraversal (NODE *root, int recursion)
{
	printf("Inorder traversed elements are below:\n");
	if (recursion)
		inorderRecursive(root);
	else
		inorderIterative(root);
	printf("\n");
}
void preorderTraversal (NODE *root, int recursion)
{
	printf("Preorder traversed elements are below:\n");
	if (recursion)
		preorderRecursive(root);
	else
		preorderIterative(root);
	printf("\n");
}

void postorderTraversal (NODE *root, int recursion)
{
	printf("Postorder traversed elements are below:\n");
	if (recursion)
		postorderRecursive(root);
	else
		postorderIterative(root);
	printf("\n");
}

NODE* findMin (NODE *root)
{
	NODE *ptr = root;
	// since the minimum value is in the left most node in BST
	while (ptr->left != NULL)
		ptr = ptr->left;
	return ptr;
}

NODE* findMax (NODE *root)
{
	NODE *ptr = root;
	// since the maximum value is in the right most node in BST
	while (ptr->right != NULL)
		ptr = ptr->right;
	return ptr;
}

NODE* insertNodeRecursive (NODE *root, int data) // inserts a node, no duplicate element allowed
{
    if (root == NULL)
        return createNode(data);
    if (data < root->info)
        root->left = insertNodeRecursive(root->left, data);
    else if (root->info < data)
        root->right = insertNodeRecursive(root->right, data);
    return root;
}

NODE* deleteNodeRecursive (NODE *root, int data)
{
	NODE *temp;
	if (root == NULL) // tree is empty
		return NULL;
	else if (data < root->info) // node to be deleted is in the left subtree
		root->left = deleteNodeRecursive(root->left, data);
	else if (root->info < data) // node to be deleted is in the right subtree
		root->right = deleteNodeRecursive(root->right, data);
	else // else root is to be deleted
	{
		if (root->left == NULL) // there is no left child
		{
			temp = root->right;
			free(root); // delete root
			return temp; // return the right subtree
		}
		else if (root->right == NULL) // there is no right child
		{
			temp = root->left;
			free(root);
			return temp; // return the left subtree
		}
		temp = findMin(root->right); // get the node with the minimum value from the right subtree
		root->info = temp->info; // delete the root's data
		root->right = deleteNodeRecursive(root->right, temp->info); // delete the temp node since it has been moved up to root
	}
	return root;
}

void inorderRecursive (NODE *root)
{
	if (root != NULL)
	{
		inorderRecursive(root->left);
		printf("%d, ", root->info);
		inorderRecursive(root->right);
	}
}

void preorderRecursive (NODE *root)
{
	if (root != NULL)
	{
		printf("%d, ", root->info);
		preorderRecursive(root->left);
		preorderRecursive(root->right);
	}
}

void postorderRecursive (NODE *root)
{
	if (root != NULL)
	{
		postorderRecursive(root->left);
		postorderRecursive(root->right);
		printf("%d, ", root->info);
	}
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

void searchNode (NODE *root, int target, NODE **par, NODE **loc) // uses iteration to find the target, modifies loc to contain the address of target node and par to contain the address of its parent
{
	NODE *save, *ptr;
	if (root == NULL) // tree is empty
	{
		*par = NULL;
		*loc = NULL;
		return;
	}
	if (target == root->info)
	{
		*par = NULL;
		*loc = root;
		return;
	}
	// initialise save and ptr pointers which will be used to traverse
	save = root;
	// if target is less than root element, the target must be in the left subtree
	// else it would be in the right subtree
	ptr = (target < root->info) ? root->left : root->right;
	// use a loop to search the tree
	while (ptr != NULL)
	{
		if (target == ptr->info)
		{
			*par = save;
			*loc = ptr;
			return;
		}
		// traverse further into the tree
		save = ptr;
		ptr = (target < ptr->info) ? ptr->left : ptr->right;
	}
	// we reach here when the search is unsuccessful
	*par = save;
	*loc = NULL;
}

void insertNodeIterative (NODE **root, int data)
{
	NODE *par, *loc;
	// search the element first
	searchNode(*root, data, &par, &loc);
	if (loc != NULL) // the data already exists, can't be inserted again
		return;
	loc = createNode(data); // else, create a new node with the provided data
	if (par == NULL) // this means, the tree is empty
		*root = loc; // so new node must become the root
	else if (data < par->info)
		par->left = loc;
	else
		par->right = loc;
}
void deleteNodeIterative (NODE **root, int target)
{
	NODE *par, *loc;
	searchNode(*root, target, &par, &loc);
	if (loc == NULL)
	{
		fprintf(stderr, "Target data (%d) not in tree, so it couldn't be deleted.", target);
		return;
	}
	if (loc->left != NULL && loc->left != NULL) // both child exists
		deleteParentOfTwo(root, &par, &loc);
	else // single or no child
		deleteSingleParent(root, &par, &loc);
}

void deleteSingleParent (NODE **root, NODE **par, NODE **loc)
{
	// loc is the node to be deleted, "child" is the child of loc
	NODE *child;
	if ((*loc)->left == NULL && (*loc)->right == NULL) // loc is childless
		child = NULL;
	else if ((*loc)->left != NULL) // left child exists
		child = (*loc)->left;
	else // right child exists
		child = (*loc)->right;
	if (*par != NULL)
	{
		if (*loc == (*par)->left) // if loc is parent's left child
			(*par)->left = child; // parent inherits loc's only child as its left child
		else // else loc must be parent's right child
			(*par)->right = child; // parent inherits loc's only child as its  right child
	}
	else // loc was the root node, so delete the root
		*root = child;
	free(*loc); // finally delete loc
}

void deleteParentOfTwo (NODE **root, NODE **par, NODE **loc)
{
	// Find the inorder successor of loc, by going to the left most node of right subtree of loc
	NODE *parsuc = *loc;
	NODE *suc = (*loc)->right;
	while (suc->left != NULL)
	{
		parsuc = suc;
		suc = suc->left;
	}
	(*loc)->info = suc->info; // replace loc's data with its inorder successor, effectively deleting the node
	deleteSingleParent(root, &parsuc, &suc); // delete the inorder successor leaf node
}

void push (SNODE **top, NODE *tNode)
{
	SNODE *newSNode = (SNODE *)malloc(sizeof(SNODE));
	if (newSNode == NULL)
	{
		fprintf(stderr, "Error: Memory not allocated.");
		exit(-1);
	}
	newSNode->treeNode = tNode;
	newSNode->link = *top;
	*top = newSNode;
}

NODE* pop (SNODE **top)
{
	SNODE *temp;
	NODE *popped;
	if (*top == NULL)
		return NULL;
	temp = *top;
	popped = temp->treeNode;
	*top = (*top)->link;
	free(temp);
	return popped;
}

NODE* peek (SNODE *top)
{
	return top->treeNode;
}

int isStackEmpty(SNODE *top)
{
	return (top == NULL);
}

// Left Subtree, Root, Right Subtree
void inorderIterative (NODE *root)
{
	NODE *current;
	SNODE *top = NULL; // stack is initially NULL
	if (root == NULL) // tree is empty, so exit the function
		return;
	current = root;
	while (current != NULL || !isStackEmpty(top))
	{
		while (current != NULL) // keep pushing the left nodes into the stack
		{
			push(&top, current);
			current = current->left;
		}
		current = pop(&top); // pop a node from the stack
		printf("%d, ", current->info); // and print it
		current = current->right; // move to the right subtree
	}
}

// Root, Left Subtree, Right Subtree
void preorderIterative (NODE *root)
{
	NODE *current;
	SNODE *top = NULL;
	if (root == NULL)
		return;
	current = root;
	while (current != NULL)
	{
		printf("%d, ", current->info);
		// by pushing the right child before left child, we essentially get the left first when popping
		if (current->right != NULL)
			push(&top, current->right);
		if (current->left != NULL)
			current = current->left;
		else
			current = pop(&top);
	}
}
// Left Subtree, Right Subtree, Root
void postorderIterative(NODE *root)
{
    NODE *current, *prev;
    SNODE *top = NULL;
    if (root == NULL) // tree is empty
        return;
    current = root;
    prev = NULL; // used to track previously visited node
    do // run atleast once, until stack is empty
    {
        // Traverse the left subtree and push nodes onto the stack
        while (current != NULL)
        {
            push(&top, current);
            current = current->left;
        }

        while (current == NULL && !isStackEmpty(top))
        {
            current = peek(top);

            // If the right subtree is not yet processed or visited
            if (current->right != NULL && current->right != prev)
            {
                current = current->right;
            }
            else
            {
                printf("%d, ", current->info);
                pop(&top);
                prev = current;
                current = NULL;
            }
        }
    } while (!isStackEmpty(top));
}

int getHeight (NODE *root)
{
	int leftHeight, rightHeight;
	if (root == NULL)
		return 0;
	leftHeight = getHeight(root->left);
	rightHeight = getHeight(root->right);
	return ((leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1);
}

void levelOrderTraversal (NODE *root)
{
	int i, height;
	if (root == NULL)
		return;
	height = getHeight(root);
	printf("Level order traversed elements are below:\n");
	for (i = 0; i < height; i++)
	{
		printCurrentLevel(root, i);
	}
}

void printCurrentLevel (NODE *root, int level)
{
	if (root == NULL || level >= getHeight(root))
		return;
	if (level == 0)
		printf("%d, ", root->info);
	else if (level > 0)
	{
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}

int countLeafNodes (NODE *root)
{
	if (root == NULL)
		return 0;
	else if (root->left == NULL && root->right == NULL)
		return 1;
	else
		return (countLeafNodes(root->left) + countLeafNodes(root->right));
}

int countNonLeafNodes (NODE *root)
{
	if (root == NULL || (root->left == NULL && root->right == NULL))
		return 0;
	else
		return (1 + countNonLeafNodes(root->left) + countNonLeafNodes(root->right));
}

void mirrorTree (NODE *root)
{
	NODE *temp;
	if (root == NULL)
		return;
	// mirror the subtrees as well
	mirrorTree(root->left);
	mirrorTree(root->right);
	// swap the left child with the right child
	temp = root->left;
	root->left = root->right;
	root->right = temp;
}


// isBST wrapper function
int isBST(NODE* root)
{
    // Use the helper function with a large range to start with
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// isBST helper function, assumes the tree has no duplicate nodes
int isBSTUtil (NODE *root, int minVal, int maxVal)
{
    // Base case: an empty tree is considered a valid binary search tree
    if (root == NULL)
        return true;

    // check if the current node's data is within the specified range
    if (root->info < minVal || root->info > maxVal)
        return false;

    // recursively checks the left and right subtrees, updating the range accordingly
    return (isBSTUtil(root->left, minVal, root->info - 1) && isBSTUtil(root->right, root->info + 1, maxVal));
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}
