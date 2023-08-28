#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node // Define NODE structure
{
	int info;
	struct node *link;
} NODE;

NODE* createNode(int data);
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
	if (head == NULL)
	{
		fprintf(stderr, "Fatal Error: List is empty.");
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
			printList(head);
			break;
		case 2:
			reverseList(&head);
			printf("Successfully reversed the list.");
			break;
		case 3:
			insertNode(&head);
			break;
		case 4:
			deleteNode(&head);
			break;
		case 5:
			printf("Which element to search?");
			scanf("%d", &searchFor);
			position = searchList(head, searchFor);
			if (position != -1)
				printf("%d found at %d'th node.", searchFor, position);
			else
				printf("%d not found in the list.", searchFor);
			break;
		default:
			printf("Invalid choice! Try again.\n");
		}
	}
	return 0;
}
NODE *createNode(int data)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Fatal Error: Memory allocation failed. \n");
		exit(-1);
	}
	newNode->info = data;
	newNode->link = NULL;
	return newNode;
}

/// @brief reads a linked list from the user
/// @param head pointer to the head of the list, passed by reference
void readList(NODE **head)
{
    int data;
    NODE *newNode = NULL;
    NODE *current = *head;

    printf("Enter the elements of the list (enter -1 to stop): ");
    while (true)
    {
        scanf("%d", &data);
        if (data == -1)
            break;
        newNode = createNode(data);
        if (*head == NULL)
            *head = newNode;
        else
            current->link = newNode;
        current = newNode;
    }   
}

void printList(NODE *head) // prints the list with , in between
{
	NODE *ptr;
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty. \n");
		return;
	}
	ptr = head;
	while (ptr != NULL)
	{
		printf("%d, ", ptr->info);
		ptr = ptr->link;
	}
	printf("\b\b \n"); // remove the last comma and space
}

/// @brief frees the memory allocated to the list
/// @param head pointer to the first node of the list, passed by reference
/// @note modifies the head pointer to NULL
void freeList(NODE** head)
{
    NODE *temp;
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->link;
		free(temp);
	}
}

/// @brief calculates the length of the list
/// @param head is the pointer to the first node of the list
/// @return the length of the list, 0 if empty
int getListLength(NODE *head)
{
	int count = 0;
	NODE *current = head;
	if (head == NULL)
		return 0;
	
	while (current != NULL)
	{
		count++;
		current = current->link;
	}
	return count;
}

/// @brief traverses to the node at the specified position
/// @param head is the pointer to the first node of the list
/// @param position is the position of the node to traverse to
/// @return the pointer to the node at the specified position, NULL if position is invalid
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
		ptr = createNode(insertThis);
		ptr->link = *head;
		*head = ptr;
		printf("\n\t %d inserted successfully at the 1st position.", insertThis);
	}
	else if (position == length+1) // last node insertion
	{
		ptr = traverseToNode(*head, length); // traverse to the last node
		ptr->link = createNode(insertThis);
		(ptr->link)->link = NULL;
		printf("\n\t %d inserted successfully at the last position.", insertThis);
	}
	else // any position
	{
		ptr = *head;
		ptr = traverseToNode(*head, position - 1); // traverse to the node before the desired position
		temp = ptr->link;
		ptr->link = createNode(insertThis);
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
	while (current != NULL)
	{
        next = current->link; // Store the next node
        current->link = prev; // Reverse the link
        // Move to the next nodes
        prev = current;
        current = next;
    }
	*head = prev;
}

/// @brief clears the input buffer
void clearBuffer (void)
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}