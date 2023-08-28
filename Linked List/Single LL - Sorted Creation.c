/*
* Objective:
** Create a single linked list in sorted manner
** meaning every element should be in sorted position
** Print the sorted Linked List
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int info;
    struct node *link;
} NODE;

NODE* createNode (int data);
void readSortedList (NODE **head);
void printList (NODE *head);
void freeList (NODE **head);

int main ()
{
    NODE *head = NULL;
    readSortedList(&head);
    printf("List is below: \n");
    printList(head);
    freeList(&head);
    return 0;
}


/// @brief creates a new node with the given data
/// @param data 
/// @return returns the pointer to the newly created node
NODE* createNode (int data)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Memory not allocated.");
        exit(EXIT_FAILURE);
    }

    newNode->info = data;
    newNode->link = NULL;
    return newNode;
}

/// @brief reads a sorted linked list from the user
/// @param head is the pointer to the head of the list, passed by reference
void readSortedList (NODE **head)
{
    int data;
    NODE *newNode = NULL;
    NODE *current = NULL;
    NODE *prev = NULL;

    printf("Enter the elements (type -1 to stop):");
    while (true)
    {
        scanf_s("%d", &data);
        if (data == -1)
            break;
        
        newNode = createNode(data);
        if (*head == NULL) // for inserting a single element
            *head = newNode;
        else
        {
            prev = NULL;
            current = *head;
            while (current != NULL && current->info < data)
            {
                prev = current;
                current = current->link;
            }
            if (prev == NULL) // if the node to be inserted is the smallest
            {
                newNode->link = *head;
                *head = newNode;
            }
            else
            {
                prev->link = newNode;
                newNode->link = current;
            }
        }
    }
}

/// @brief prints the linked list in the format: 1, 2, 3
/// @param head is the pointer to the head of the list
void printList (NODE *head)
{
    NODE *current = head;
    if (head == NULL)
    {
        fprintf(stderr, "Error: List is empty. \n");
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

/// @brief deletes the entire list and sets the head to NULL
/// @param head is the pointer to the head of the list, passed by reference
void freeList (NODE **head)
{
    NODE *current = *head;
    NODE *temp = NULL;

    while (current != NULL)
    {
        temp = current;
        current = current->link;
        free(temp);
    }
    *head = NULL;
}