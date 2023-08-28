/*
* Objective: 
** Get two sorted singly linked lists (sort them in ascending order automatically)
** Menu to concatinate or merge
** Concatinate: Add second list to the end of first list
** Merge: Merge two lists in sorted order
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
void concatinateList (NODE *head1, NODE *head2);
NODE* mergeList (NODE *head1, NODE *head2);
void freeList (NODE **head);

int main ()
{
    NODE *head1 = NULL, *head2 = NULL, *mergedHead = NULL;
    int option;

    while (true)
    {
        printf("** Main Menu **\n");
        printf("1. Read two sorted lists\n");
        printf("2. Print two lists\n");
        printf("3. Concatinate two lists (list2 at the end of list1)\n");
        printf("4. Merge two lists\n");
        printf("5. Delete two lists\n");
        printf("6. Exit\n");

        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                printf("List 1:\n");
                readSortedList(&head1);
                printf("List 2:\n");
                readSortedList(&head2);
                break;
            case 2:
                printf("List 1 is below: \n");
                printList(head1);
                printf("List 2 is below: \n");
                printList(head2);
                break;
            case 3:
                concatinateList(head1, head2);
                printf("List 1 after concatination: \n");
                printList(head1);
                break;
            case 4:
                freeList(&mergedHead); // first clear the merged list
                mergedHead = mergeList(head1, head2); // merge the lists
                printf("Merged list is below: \n");
                printList(mergedHead);
                break;
            case 5:
                freeList(&head1);
                freeList(&head2);
                freeList(&mergedHead);
                printf("Lists deleted.\n");
                break;
            case 6:
                freeList(&head1);
                freeList(&head2);
                freeList(&mergedHead);
                printf("Program exited.\n");
                exit(0);
            default:
                printf("Invalid option. Please try again. \n");
        }
    }

    return 0;
}
/// @brief creates a new node with the given data
/// @param data 
/// @return the pointer to the newly created node
NODE* createNode (int data)
{
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Memory not allocated.");
        exit(-1);
    }
    newNode->info = data;
    newNode->link = NULL;
    return newNode;
}

/// @brief reads elements of a list and sorts them in ascending order
/// @param head is modified to point to the first node of the list, passed by reference
void readSortedList (NODE **head)
{
    NODE *current, *newNode;
    int data;
    printf("Enter elements of list in ascending order (Enter -1 to terminate): ");
    // read until -1 is encountered
    while (true)
    {
        scanf("%d", &data);
        if (data == -1)
            break;
        newNode = createNode(data);
        if (*head == NULL)
            *head = newNode;
        else
        {
            current = *head;
            while (current->info < newNode->info && current->link != NULL)
                current = current->link;
            newNode->link = current->link;
            current->link = newNode;
        }
    }
}

/// @brief prints a linked list in the format: 1-> 2-> 3
/// @param head is the pointer to the first node of the list
void printList(NODE *head)
{
    NODE *current = head;
    if (head == NULL)
    {
        fprintf(stderr, "List is empty.\n");
        return;
    }
    while (current != NULL)
    {
        printf("%d", current->info);
        if (current->link != NULL)
            printf("-> ");
        current = current->link;
    }
    printf("\n");
}

/// @brief concatinates list2 at the end of list1
/// @param head1 head of list1
/// @param head2 head of list2
void concatinateList (NODE *head1, NODE *head2)
{
    NODE *current = head1;
    if (head1 == NULL || head2 == NULL)
    {
        fprintf(stderr, "Error: Lists cannot be empty.\n");
        return;
    }
    while (current->link != NULL)
        current = current->link;
    current->link = head2;
}

/// @brief merge two sorted lists in ascending order
/// @param head1 is the head of the first list
/// @param head2 is the head of the second list
/// @return the head of the merged list
NODE* mergeList (NODE *head1, NODE *head2)
{
    NODE *newNode = NULL;
    NODE *current1 = head1, *current2 = head2;
    NODE *mergedHead = NULL, *mergedCurrent = NULL;
    if (head1 == NULL || head2 == NULL)
    {
        fprintf(stderr, "Error: Lists can not be empty.\n");
        return NULL;
    }

    while (current1 != NULL && current2 != NULL) // until any one list ends
    {
        // Select the appropiate element from the lists
        if (current1->info < current2->info) // if first list's current element is smaller
        {
            newNode = createNode(current1->info);
            current1 = current1->link;
        }
        else if (current2->info < current1->info) // if second list's current element is smaller
        {
            newNode = createNode(current2->info);
            current2 = current2->link;
        }
        else // both list's current element is equal
        {
            newNode = createNode(current1->info);
            current1 = current1->link;
            current2 = current2->link;
        }

        // insert the selected element in the merged list
        if (mergedHead == NULL)
            mergedHead = newNode;
        else
            mergedCurrent->link = newNode;
        mergedCurrent = newNode;
    }

    // if any list is not empty, add the remaining elements to the merged list
    // check and add the remaining elements of first list
    while (current1 != NULL)
    {
        newNode = createNode(current1->info);
        mergedCurrent->link = newNode;
        mergedCurrent = newNode;
        current1 = current1->link;
    }
    // check and add the remaining elements of second list
    while (current2 != NULL)
    {
        newNode = createNode(current2->info);
        mergedCurrent->link = newNode;
        mergedCurrent = newNode;
        current2 = current2->link;
    }

    return mergedHead;
}
/// @brief Free the memory allocated to the list and set the head to NULL
/// @param head Pointer to the head of the list
void freeList (NODE **head)
{
    NODE *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->link;
        free(temp);
    }
}