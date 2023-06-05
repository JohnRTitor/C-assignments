#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node // Define NODE structure
{
	int info;
	struct node *link;
} NODE;

NODE *getNode(int data);
void createList(NODE **head);
void printList(NODE *head);
void freeList(NODE **head);
int getListLength(NODE *head);
NODE *traverseToNode(NODE *head, int position);
void listCat(NODE *head1, NODE *head2);

int main()
{
	NODE *head1, *head2; // head node's link here contains the first node's pointer
	/* create list and modify head pointer */
	printf("Enter List#1:\n");
	createList(&head1);
	printf("Enter List#2:\n");
	createList(&head2);

	listCat(head1->link, head2->link);

	printf("\nSuccessfully appended list#2 at the end of list#1. New list is below.\n");
	printList(head1->link);

	freeList(&head1); // free the list
	free(head2);

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
void printList(NODE *head)
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

void freeList(NODE **head) // frre the entire list and modify head to null
{
	NODE *current, *next;
	current = *head;
	while (current != NULL)
	{
		next = current->link; // store the next link
		free(current);		  // free current node
		current = next;		  // next node becomes current
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

void listCat(NODE *head1, NODE *head2) // append list1 at the end of list1
{
	NODE *last1;
	int length1;

	if (head1 == NULL || head2 == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		exit(-1);
	}

	length1 = getListLength(head1);			// calculate the length of list1
	last1 = traverseToNode(head1, length1); // get list1's last node's pointer
	last1->link = head2;					// concatinate list2 at the end of list1
}