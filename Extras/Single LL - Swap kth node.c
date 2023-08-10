/*
* Objective:-
** Get a single linked list
** get the value for k as position
** swap k'th node to k+1'th node
** print the list
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *link;
} NODE;

NODE *createNode (int data);
NODE *createList ();
void printList (NODE *head);
bool swapKthNodes (NODE *head, int k);

int main ()
{
    NODE *head = NULL;
    int k;
    printf("Input Linked List:\n");
    head = createList ();
    printf("Enter the position of the node to be swapped: ");
    scanf("%d", &k);
    if (swapKthNodes (head, k))
        printList (head);
    else
        printf("Error: Invalid position!\n");
    return 0;
}

NODE *createNode (int data)
{
    NODE *newNode = (NODE *) malloc (sizeof (NODE));
    if (newNode == NULL)
    {
        printf ("Error: Memory allocation failed!\n");
        exit (-1);
    }
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

NODE *createList ()
{
    NODE *head = NULL, *newNode = NULL, *temp = NULL;
    int data;
    printf("Enter the data for the node (Enter -1 to stop): ");
    scanf("%d", &data);
    while (data != -1)
    {
        newNode = createNode (data);
        if (head == NULL)
            head = newNode;
        else
            temp->link = newNode;
        temp = newNode;
        printf("Enter the data for the node (Enter -1 to stop): ");
        scanf("%d", &data);
    }
    return head;
}

void printList (NODE *head)
{
    NODE *temp = head;
    printf("The list is: ");
    while (temp != NULL)
    {
        printf("%d", temp->data);
        if (temp->link != NULL)
            printf("--> ");
        temp = temp->link;
    }
    printf("\n");
}

bool swapKthNodes (NODE *head, int k)
{
    NODE *temp = NULL;
    NODE *current = head;
    int count = 0;

    if (k < 1) 
        return false;

    while (current != NULL)
    {
        if (count == k - 1)
        {
            temp = current -> link;
            current->link = temp->link;
            temp->link = current;
            return true;
        }
        count++;
        current = current->link;
    }
    return false;
}
