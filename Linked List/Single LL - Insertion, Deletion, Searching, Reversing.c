#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node // Define NODE structure
{
	int info;
	struct node *link;
} NODE;
NODE* getNode(int data);
void createList(NODE **head);
void printList(NODE *head);
void freeList(NODE** head);
int getListLength(NODE *head);
NODE* traverseToNode(NODE *head, int position);
int searchList(NODE *head, int searchFor);
void insertNode(NODE **head);
void deleteNode(NODE **head);
void reverseList(NODE **head);
void clearBuffer (void);
int main()
{
	NODE *head;
	int option, searchFor, position;
	
	createList(&head); // create list and modify head pointer
	
	/* head node's link here contains the first node's pointer */
	if (head->link == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		exit(-1);
	}
	
	while (true)
	{
		printf("\n\n**** MENU ****\n");
		printf(" 1. Print List\n 2. Reverse List\n 3. Insert Node\n 4. Delete Node\n 5. Search for an element in the list\n 6. Exit\n");
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
			printList(head->link);
			break;
		case 2:
			reverseList(&(head->link));
			printf("Successfully reversed the list.");
			break;
		case 3:
			insertNode(&(head->link));
			break;
		case 4:
			deleteNode(&(head->link));
			break;
		case 5:
			printf("Which element to search?");
			scanf("%d", &searchFor);
			position = searchList(head->link, searchFor);
			if (position != -1)
			{
				printf("%d found at %d'th node.", searchFor, position);
			}
			else
			{
				printf("%d not found in the list.", searchFor);
			}
			break;
		default:
			printf("Invalid choice! Try again.\n");
		}
	}
	return 0;
}
NODE *getNode(int data)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		exit(-1);
	}
	newNode->info = data;
	newNode->link = NULL;
	return newNode;
}
void createList(NODE **head)
{
	int i, data, size;
	NODE *ptr;
	*head = getNode(0); // create head node, head->link will contains the address of first node
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
		ptr->link = getNode(data);
		ptr = ptr->link;
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
		ptr = ptr->link;
	}
}
// Function to free the entire linked list
void freeList(NODE** head) // frre the entire list and modify head to null
{
    NODE *current, *next;
    current = *head;
    while (current != NULL) {
        next = current->link; // store the next link
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
		ptr = ptr->link;
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
		ptr = ptr->link;
	}
	if (count == position) // Check if count matches position
	{
		return ptr;
	}
	return NULL; // Return NULL if position is invalid or out of bounds
}
int searchList(NODE *head, int target) // returns the position if found else returns -1
{
	int count = 1;
	NODE *ptr = head;
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty.\n");
		return -1;
	}
	while (ptr != NULL)
	{
		if (ptr->info == target)
		{
			return count;
		}
		count++;
		ptr = ptr->link;
	}
	return -1;
}
void insertNode(NODE **head) // inserts a node in the position specified by user, head can be modified if need
{
	NODE *ptr, *temp;
	int option, insertThis, length, position;
	
	if (*head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return;
	}
	length = getListLength(*head);
	printf("\n\t 1. 1st node insertion. \n\t %d. Last node insertion \n\t Or just enter the position of your choice (range 1-%d):", length+1, length);
	scanf("%d", &option);
	printf("\n\tEnter data to insert:");
	if (scanf("%d", &insertThis) != 1 || length < 1 || option < 1 || option > length+1) // input and error checking
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
		ptr = getNode(insertThis);
		ptr->link = *head;
		*head = ptr;
		printf("\n\t %d inserted successfully at the 1st position.", insertThis);
	}
	else if (position == length+1) // last node insertion
	{
		ptr = traverseToNode(*head, length); // traverse to the last node
		ptr->link = getNode(insertThis);
		(ptr->link)->link = NULL;
		printf("\n\t %d inserted successfully at the last position.", insertThis);
	}
	else // any position
	{
		ptr = *head;
		ptr = traverseToNode(*head, position - 1); // traverse to the node before the desired position
		temp = ptr->link;
		ptr->link = getNode(insertThis);
		(ptr->link)->link = temp;
		printf("\n\t %d inserted successfully at the position#%d", insertThis, position);
	}
}
void deleteNode(NODE **head) // deletes a node from a specific position or via searching, head value can be modified if needed
{
	NODE *ptr, *temp;
	int count, option, length, position, searchFor;
	
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
		printf("\n\t Enter value to search for. Note: This only deletes the first occurance:");
		scanf("%d", &searchFor);
		count = 1;
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
		*head = (*head)->link;
		free(ptr);
	}
	else if (position == length) // last node deletion
	{
		ptr = traverseToNode(*head, length - 1); // traverse to the node before the last node
		free(ptr->link);
		ptr->link = NULL;
	}
	else // any position deletion
	{
		ptr = traverseToNode(*head, position - 1); // traverse to the node before the position
		temp = ptr->link;
		ptr->link = (ptr->link)->link;
		free(temp);
	}
	printf("\n\t Node successfully deleted.");
}
void reverseList (NODE **head) // reverses a linked list
{
	NODE *current, *prev, *next;
	if (*head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return;
	}
	current = *head;
	prev = NULL;
	next = NULL;
	while (current != NULL) {
        next = current->link; // Store the next node
        current->link = prev; // Reverse the link
        // Move to the next nodes
        prev = current;
        current = next;
    }
	*head = prev;
}
void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}