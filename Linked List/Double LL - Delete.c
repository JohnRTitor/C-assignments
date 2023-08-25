#include <stdio.h>
#include <stdlib.h>

typedef struct node // Define NODE structure
{
	int info;
	struct node *prev; // previous link
	struct node *next; // next link
} NODE;


NODE *createNode(int data, NODE *prevLink);
void createList(NODE **head);
void printList(NODE *head);
void freeList(NODE** head);
int getListLength(NODE *head);
NODE* searchList(NODE *head, int target, int *position);
void deleteNode(NODE **head);


int main()
{
	NODE *head;
	createList(&head);
	printf("You entered: \n");
	printList(head->next);
	
	deleteNode(&(head->next));
	printf("After Deletion:\n");
	printList(head->next);
	freeList(&head);
	return 0;
}

NODE *createNode(int data, NODE *prevLink)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		exit(-1);
	}
	newNode->info = data;
	newNode->prev = prevLink;
	newNode->next = NULL;
	return newNode;
}

void createList(NODE **head)
{
	int i, data, size;
	NODE *ptr;
	*head = createNode(0, NULL); // create empty head node, head->next will contains the address of first node
	printf("How many nodes to create?");
	scanf("%d", &size);
	if (size < 1 || *head == NULL)
	{
		fprintf(stderr, "Error: Invalid size/List could not be made.\n");
		return;
	}
	ptr = *head;
	for (i = 1; i <= size; i++)
	{
		printf("NODE#%d - Enter data to insert:", i);
		scanf("%d", &data);
		ptr->next = createNode(data, ptr); // pass the read data and prev pointer's value
		ptr = ptr->next;
	}
}

void printList(NODE *head) // prints the list with , in between
{
	NODE *ptr;
	if (head == NULL)
	{
		fprintf(stderr, "\nError: List is empty.");
		return;
	}
	ptr = head;
	while (ptr != NULL)
	{
		printf("%d, ", ptr->info);
		ptr = ptr->next;
	}
}

// Function to free the entire nexted list
void freeList(NODE** head) // frre the entire list and modify head to null
{
    NODE *current, *next;
    current = *head;
    while (current != NULL) {
        next = current->next; // store the next next
        free(current); // free current node
        current = next; // next node becomes current
    }
    *head = NULL;
}

int getListLength(NODE *head)
{
	int count = 0;
	NODE *ptr = head;
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return 0;
	}
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return count;
}

NODE* searchList(NODE *head, int target, int *position) // returns the location of the element if found, else returns NULL
{
    int count = 0;
    NODE *ptr = head;
    if (head == NULL)
    {
        fprintf(stderr, "Error: List is empty.\n");
        return NULL;
    }
    while (ptr != NULL)
    {
        count++;
        if (ptr->info == target)
        {
            *position = count;
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void deleteNode(NODE **head) // deletes a node by the given respective elemen, head value can be modified if needed
{
	NODE *ptr, *location;
	int length, position, searchFor;

	if (*head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return;
	}
	length = getListLength(*head);

	printf("\nEnter value to search for. Note: This only deletes the first occurance:");
	scanf("%d", &searchFor);
	location = searchList(*head, searchFor, &position);
	if (location == NULL)
	{
		printf("\nNot found, so couldn't be deleted.\n");
		return;
	}
	
	/* target element found */
	printf("\n%d found at position#%d.\n", searchFor, position);

	if (position == 1) // first node deletion
	{
		ptr = *head;
		*head = (*head)->next;
		free(ptr);
	}
	else if (position == length) // last node deletion
	{
		ptr = location->prev;
		free(ptr->next);
		ptr->next = NULL;
	}
	else // any position deletion
	{
		ptr = location->prev;
		ptr->next = location->next;
		free(location);
	}
	printf("\nNode successfully deleted.");
}
