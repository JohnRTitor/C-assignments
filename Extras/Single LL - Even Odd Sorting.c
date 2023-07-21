/*
* Objective:
** get a linked list of integers from user
** get the odd and even lists from the original list
** print the odd and even lists
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int info;
    struct node *link;
} NODE;


NODE* createNode(int data);
void readList (NODE **head);
void printList (NODE *head);
void getEvenOddLists (NODE *head, NODE **evenHead, NODE **oddHead);

int main ()
{
    NODE *head = NULL;
    NODE *evenHead = NULL;
    NODE *oddHead = NULL;

    readList(&head);
    getEvenOddLists(head, &evenHead, &oddHead);

    printf("The even elements are: ");
    printList(evenHead);
    printf("The odd elements are: ");
    printList(oddHead);

    return 0;
}

NODE* createNode(int data)
{
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    newNode->info = data;
    newNode->link = NULL;
    return newNode;
}

void readList (NODE **head)
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

void printList (NODE *head)
{
    NODE *current = head;
    
    if (head == NULL)
    {
        fprintf(stderr, "Error: List is empty.");
        return;
    }

    while (current != NULL)
    {
        printf("%d", current->info);
        if (current->link != NULL)
            printf(", ");
        current = current->link;
    }
    printf("\n");
}

void getEvenOddLists (NODE *head, NODE **evenHead, NODE **oddHead)
{
    NODE *newNode = NULL;
    NODE *current = head;
    NODE *evenCurrent = NULL;
    NODE *oddCurrent = NULL;

    if (head == NULL)
    {
        fprintf(stderr, "Error: List is empty.\n");
        return;
    }

    while (current != NULL)
    {
        newNode = createNode(current->info);
        if (current->info % 2 == 0)
        {
            if (*evenHead == NULL)
                *evenHead = newNode;
            else
                evenCurrent->link = newNode;
            evenCurrent = newNode;
        }
        else
        {
            if (*oddHead == NULL)
                *oddHead = newNode;
            else
                oddCurrent->link = newNode;
            oddCurrent = newNode;
        }
        current = current->link;
    }
}