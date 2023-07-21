/*
* Objectives:-
** get two linked lists (head1, head2) from user
** create a menu:
*** print the union of the two lists
*** print the intersection of the two lists
*** re enter the lists
*** exit
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
void readList(NODE **head);
void printList (NODE *head);
NODE* searchList (NODE *head, int searchFor);
NODE* listUnion (NODE *head1, NODE *head2);
NODE* listIntersection (NODE *head1, NODE *head2);
void freeList (NODE **head);

int main ()
{
    NODE *head1 = NULL, *head2 = NULL;
    NODE *unionHead = NULL, *intersectionHead = NULL;
    int choice;
    
    while (true)
    {
        printf("\nMain Menu: \n");
        printf("1. Enter the elements of the list, if list is not empty, it appends the new elements \n");
        printf("2. Print the lists \n");
        printf("3. Print the union of the lists \n");
        printf("4. Print the intersection of the lists \n");
        printf("5. Delete the lists \n");
        printf("6. Exit \n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("List 1: \n");
                readList(&head1);
                printf("List 2: \n");
                readList(&head2);
                break;
            case 2:
                printf("List 1: ");
                printList(head1);
                printf("List 2: ");
                printList(head2);
                break;
            case 3:
                unionHead = listUnion(head1, head2);
                printf("The union of the lists is: ");
                printList(unionHead);
                break;
            case 4:
                intersectionHead = listIntersection(head1, head2);
                printf("The intersection of the lists is: ");
                printList(intersectionHead);
                break;
            case 5:
                freeList(&head1);
                freeList(&head2);
                freeList(&unionHead);
                freeList(&intersectionHead);
                printf("Lists deleted.\n");
                break;
            case 6:
                printf("Program exited. \n");
                freeList(&head1);
                freeList(&head2);
                freeList(&unionHead);
                freeList(&intersectionHead);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Invalid choice. \n");
        }
    }

    return 0;
}

NODE* createNode(int data)
{
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->info = data;
    newNode->link = NULL;
    return newNode;
}

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
        {
            *head = newNode;
            current = newNode;
        }
        else
        {
            current->link = newNode;
            current = newNode;
        }
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

NODE* searchList (NODE *head, int searchFor)
{
    NODE *current = head;

    if (head == NULL)
        return NULL;

    while (current != NULL && current->info != searchFor)
    {
        current = current->link;
    }
    return current;
}

NODE* listUnion (NODE *head1, NODE *head2)
{
    NODE *newNode = NULL;
    NODE *current1 = head1, *current2 = head2;
    NODE *unionHead = NULL, *unionCurrent = NULL;

    /*
    * First copy the entire content of list1 (head1) to union list
    * Then copy each element of the list2 (head2) provided
    * it does not already exist in the union list
    */
    while (current1 != NULL)
    {
        newNode = createNode(current1->info);
        if (unionHead == NULL)
        {
            unionHead = newNode;
            unionCurrent = newNode;
        }
        else
        {
            unionCurrent->link = newNode;
            unionCurrent = unionCurrent->link;
        }
        current1 = current1->link;
    }

    while (current2 != NULL)
    {
        if (searchList(unionHead, current2->info) == NULL)
        {
            newNode = createNode(current2->info);
            unionCurrent->link = newNode;
            unionCurrent = unionCurrent->link;
        }
        current2 = current2->link;
    }
    return unionHead;
}

NODE* listIntersection (NODE *head1, NODE *head2)
{
    NODE *newNode = NULL;
    NODE *current1 = head1;
    NODE *intersectionHead = NULL, *intersectionCurrent = NULL;

    while (current1 != NULL)
    {
        // for each element of list1, if also present in list2
        // add to intersection list
        if (searchList(head2, current1->info))
        {
            newNode = createNode(current1->info);
            if (intersectionHead == NULL)
            {
                intersectionHead = newNode;
                intersectionCurrent = newNode;
            }
            else
            {
                intersectionCurrent->link = newNode;
                intersectionCurrent = intersectionCurrent->link;
            }
        }
        current1 = current1->link;
    }
    return intersectionHead;
}

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