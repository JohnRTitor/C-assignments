#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Menu for Double Linked List: includes reading, printing, insertion and deletion of nodes */

typedef struct node // Define NODE structure
{
	int info;
	struct node *prev;
	struct node *next;
} NODE;

NODE* createNode(int data, NODE *prevLink);
void createList(NODE **head);
void printList(NODE *head);
void freeList(NODE** head);
int getListLength(NODE *head);
NODE* traverseToNode(NODE *head, int position);
int searchList(NODE *head, int searchFor);
void insertNode(NODE **head);
void deleteNode(NODE **head);
void clearBuffer (void);

int main()
{
	NODE *head;
	int option, searchFor, position;
	
	createList(&head); // create list and modify head pointer
	
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		exit(-1);
	}
	
	while (true)
	{
		printf("\n\n**** MENU ****\n");
		printf(" 1. Print List\n 2. Insert Node\n 3. Delete Node\n 4. Search for an element in the list\n 5. Re-enter list\n 6. Exit\n");
		printf("Enter your choice: ");
		clearBuffer();
		scanf("%d", &option);
		
		if (option == 6)
		{
			printf("\nProgram exited.");
			freeList(&head);
			exit(1);
		}

		switch (option)
		{
		case 1:
			printList(head);
			break;

		case 2:
			insertNode(&head);
			break;

		case 3:
			deleteNode(&head);
			break;

		case 4:
			printf("Which element to search?");
			scanf("%d", &searchFor);
			position = searchList(head, searchFor);
			if (position != -1)
			{
				printf("%d found at %d'th node.", searchFor, position);
			}
			else
			{
				printf("%d not found in the list.", searchFor);
			}
			break;
		case 5:
			printf("\n Please re-enter the list.\n");
			freeList(&head);
			createList(&head);
			break;

		default:
			printf("Invalid choice! Try again.\n");
		}
	}
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
	*head = NULL; // without creating a head node
	printf("How many nodes to create?");
	scanf("%d", &size);
	if (size < 1)
	{
		fprintf(stderr, "Error: Invalid size/List could not be made.\n");
		return;
	}
	for (i = 1; i <= size; i++)
	{
		printf("NODE#%d - Enter data to insert:", i);
		scanf("%d", &data);
		if (*head == NULL)
		{
			*head = createNode(data, NULL);
			ptr = *head;
		}
		else
		{
			ptr->next = createNode(data, ptr);
			ptr = ptr->next;
		}
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
		printf("%d", ptr->info);
		if (ptr->next != NULL)
		{
			printf(", ");
		}
		ptr = ptr->next;
	}
}

void freeList(NODE** head) // free the entire list and modify head to null
{
    NODE *current, *temp;
    current = *head;
    while (current != NULL)
    {
         temp = current;
         current = current->next;
         free(temp);
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

NODE *traverseToNode(NODE *head, int position)
{
	int count = 1; // positioning starts from 1
	NODE *ptr = head;
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return NULL;
	}
	while (ptr != NULL && count < position) // Until count reaches positon
	{
		count++;
		ptr = ptr->next;
	}
	if (count == position) // Check if count matches position
	{
		return ptr;
	}
	return NULL; // Return NULL if position is invalid or out of bounds
}

int searchList(NODE *head, int target) // returns the position if found else returns -1
{
	int count = 0;
	NODE *ptr = head;
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty.\n");
		return -1;
	}
	while (ptr != NULL)
	{
		count++;
		if (ptr->info == target)
		{
			return count;
		}
		ptr = ptr->next;
	}
	return -1;
}
void insertNode(NODE **head) // inserts a node in the position specified by user, head can be modified if needed
{
	NODE *ptr, *temp;
	int option, insertThis, length, position;

	if (*head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		printf("\nDo you want to insert a node? Press 1.");
		scanf("%d", &option);
		if (option == 1)
		{
			printf("Enter the data to insert:");
			scanf("%d", &insertThis);
			*head = createNode(insertThis, NULL);
			printf("\nSuccessfully inserted.");
		}
		else
		{
			printf("\n You chose to not insert a node.");
		}
		return;
	}
	length = getListLength(*head);

	printf("\n\t 1. 1st node insertion. \n\t %d. Last node insertion \n\t Or just enter the position of your choice (range 1-%d):", length + 1, length);
	scanf("%d", &option);
	printf("\n\tEnter data to insert:");

	if (scanf("%d", &insertThis) != 1 || length < 1 || option < 1 || option > length + 1) // input and error checking
	{
		fprintf(stderr, "\n\tError: Data could not be inserted in said position.");
		return;
	}
	else
	{
		position = option;
	}

	if (position == 1) // first node insertion
	{
		ptr = createNode(insertThis, NULL);
		ptr->next = *head;
		*head = ptr;
		printf("\n\t %d inserted successfully at the 1st position.", insertThis);
	}
	else if (position == length + 1) // last node insertion
	{
		ptr = traverseToNode(*head, length); // traverse to the last node
		ptr->next = createNode(insertThis, ptr);
		printf("\n\t %d inserted successfully at the last position.", insertThis);
	}
	else // any position
	{
		ptr = traverseToNode(*head, position - 1); // traverse to the node before the desired position
		temp = ptr->next;
		ptr->next = createNode(insertThis, ptr);
		(ptr->next)->next = temp;
		temp->prev = ptr->next;
		printf("\n\t %d inserted successfully at the position#%d", insertThis, position);
	}
}

void deleteNode(NODE **head) // deletes a node from a specific position or via searching, head value can be modified if needed
{
	NODE *ptr, *temp;
	int option, length, position, searchFor;
	
	if (*head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return;
	}
	length = getListLength(*head);

	printf("\n\t 0. Search by value. \n\t 1. Delete 1st node. \n\t %d. Delete last node. \n\t Or just enter the position of your choice (range 1-%d):", length, length);
	scanf("%d", &option);

	if (length < 1 || option < 0 || option > length) // input and error checking
	{
		fprintf(stderr, "\n\t Error. Node could not be deleted.");
		return;
	}
	else if (option == 0) // if user chooses to search by value, take input and search it first
	{
		printf("\n\t Enter value to search for. Note: This only deletes the first occurrence:");
		scanf("%d", &searchFor);
		position = searchList(*head, searchFor);
		if (position != -1)
		{
			printf("\n\t %d found at position#%d.\n", searchFor, position);
		}
		else
		{
			printf("\n\t Not found, so couldn't be deleted.\n");
			return;
		}
	}
	else
	{
		position = option;
	}

	/* position has been found by search/or user entered a valid position */

	if (position == 1) // first node deletion
	{
		ptr = *head;
		*head = (*head)->next;
		(*head)->prev = NULL;
		free(ptr);
	}
	else if (position == length) // last node deletion
	{
		ptr = traverseToNode(*head, length - 1); // traverse to the node before the last node
		free(ptr->next);
		ptr->next = NULL;
	}
	else // any position deletion
	{
		temp = traverseToNode(*head, position); // traverse to node to be deleted
		ptr = temp->prev; // get the previous link
		ptr->next = temp->next;
		(ptr->next)->prev = ptr;
		free(temp);
	}
	printf("\nNode#%d successfully deleted.", position);
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}