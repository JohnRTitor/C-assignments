/*
* Objectives:-
** get two sets as linked list (head1, head2) from user
** create a menu:
*** print the union of the two sets
*** print the intersection of the two sets
*** re enter the sets
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

NODE* createNode (int data);
void readSet (NODE **head);
void printList (NODE *head, char listName[]);
NODE* searchList (NODE *head, int searchFor);
NODE* setUnion (NODE *head1, NODE *head2);
NODE* setIntersection (NODE *head1, NODE *head2);
void freeList (NODE **head);
void clearInputBuffer (void);

int main ()
{
    NODE *head1 = NULL, *head2 = NULL;
    NODE *unionHead = NULL, *intersectionHead = NULL;
    int choice;
    
    while (true)
    {
        printf("\nMain Menu: \n");
        printf("1. Enter the elements of the sets. For non-empty sets, it appends the new elements \n");
        if (head1 != NULL || head2 != NULL) // atleast one set needs to be non-empty to perform the following actions
        {
            printf("2. Print the sets \n");
            printf("3. Print the union of the sets \n");
            printf("4. Print the intersection of the sets \n");
            printf("5. Delete the sets \n");
        }
        printf("6. Exit \n");
        if (head1 == NULL && head2 == NULL)
            printf("Note: Few actions are available due to both sets being empty. \n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "Error: Invalid input. \n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                printf("Set A: \n");
                readSet(&head1);
                printf("Set B: \n");
                readSet(&head2);
                break;
            case 2:
                printList(head1, "Set A");
                printList(head2, "Set B");
                break;
            case 3:
                unionHead = setUnion(head1, head2);
                printList(unionHead, "Union Set (A U B)");
                break;
            case 4:
                intersectionHead = setIntersection(head1, head2);
                if (intersectionHead != NULL)
                {
                    printList(intersectionHead, "Intersection Set (A ∩ B)");
                }
                else
                    printf("No common elements between the sets A and B. Intersection Set is empty. \n");
                break;
            case 5:
                if (head1 == NULL)
                {
                    printf("Set A is already empty. Set B deleted. \n");
                    freeList(&head2);
                }
                else if (head2 == NULL)
                {
                    printf("Set A deleted. Set B is already empty. \n");
                    freeList(&head1);
                }
                else
                {
                    printf("Both sets deleted. \n");
                    freeList(&head1);
                    freeList(&head2);
                }
                printf("Cached union and intersection sets also deleted. \n");
                freeList(&unionHead);
                freeList(&intersectionHead);
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
                printf("Invalid choice. Please try again. \n");
        }
    }

    return 0;
}

/// @brief creates a new node with the given data
/// @param data 
/// @return returns the pointer to the newly created node
NODE* createNode(int data)
{
    NODE *newNode = (NODE*) malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        fprintf(stderr, "Fatal Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->info = data;
    newNode->link = NULL;
    return newNode;
}

/// @brief reads a set (linked list) from the user
/// @param head pointer to the first element of the set, passed by reference
/// @note if the set is not empty, the new elements are appended to the set
void readSet (NODE **head)
{
    int data;
    NODE *newNode = NULL;
    NODE *current = *head;

    if (*head != NULL)
        printf("Note: Appending \n");
    
    printf("Enter space-separated integers (-1 to stop): ");
    while (true)
    {
        if (scanf("%d", &data) != 1) // handle invalid inputs and clear the input buffer
        {
            fprintf(stderr, "Error: Invalid input. Try again. \n");
            clearInputBuffer();
            continue;
        }
        if (data == -1) // terminate if -1 is entered
            break;
        if (searchList(*head, data) != NULL) // if the element already exists in the list, skip it with a warning
        {
            fprintf(stderr, "Warning: %d already exists in the set. Skipped \n", data);
            continue;
        }

        newNode = createNode(data);
        if (*head == NULL)
            *head = newNode;
        else
            current->link = newNode;
        current = newNode;
    }   
}

/// @brief prints the linked list in the format: 1, 2, 3
/// @param head is the pointer to the head of the list
/// @param listName is the name of the list to be printed
void printList (NODE *head, char listName[])
{
    NODE *current = head;
    
    if (head == NULL)
    {
        fprintf(stderr, "Error: %s is empty.", listName);
        return;
    }

    printf("%s: ", listName);
    while (current != NULL)
    {
        printf("%d", current->info);
        if (current->link != NULL)
            printf(", ");
        current = current->link;
    }
    printf("\n");
}

/// @brief searches for the given element in the list
/// @param head 
/// @param searchFor is the element to be searched for
/// @return returns the pointer to the node containing the element, else returns NULL
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

/// @brief Get the union of the two sets
/// @param head1 is pointer to the first element of first set
/// @param head2 is pointer to the first element of second set
/// @return the pointer to the first element of the union set
NODE* setUnion (NODE *head1, NODE *head2)
{
    NODE *newNode = NULL;
    NODE *current1 = head1, *current2 = head2;
    NODE *unionHead = NULL, *unionCurrent = NULL;

    // First copy the entire content of list1 (head1) to union list
    while (current1 != NULL)
    {
        newNode = createNode(current1->info);
        if (unionHead == NULL)
            unionHead = newNode;
        else
            unionCurrent->link = newNode;
        unionCurrent = newNode;
        current1 = current1->link; // traverse list1
    }
    /*
    * Then copy each element of the list2 (head2) provided
    * it does not already exist in the union list
    */
    while (current2 != NULL)
    {
        if (searchList(unionHead, current2->info) == NULL)
        {
            newNode = createNode(current2->info);
            if (unionHead == NULL)
                unionHead = newNode;
            else
                unionCurrent->link = newNode;
            unionCurrent = newNode;
        }
        current2 = current2->link; // traverse list2
    }
    return unionHead;
}

/// @brief Get the intersection of the two sets
/// @param head1 is pointer to the first element of first set
/// @param head2 is pointer to the first element of second set
/// @return the pointer to the first element of the intersection set
NODE* setIntersection (NODE *head1, NODE *head2)
{
    NODE *newNode = NULL;
    NODE *current1 = head1;
    NODE *intersectionHead = NULL, *intersectionCurrent = NULL;

    if (head1 == NULL || head2 == NULL) // if either of the set is empty, the intersection set should also be empty
        return NULL;

    while (current1 != NULL)
    {
        // for each element of list1, if also present in list2
        // add to intersection list
        if (searchList(head2, current1->info))
        {
            newNode = createNode(current1->info);
            if (intersectionHead == NULL)
                intersectionHead = newNode;
            else
                intersectionCurrent->link = newNode;
            intersectionCurrent = newNode;
        }
        current1 = current1->link; // traverse list1
    }
    return intersectionHead;
}

/// @brief deletes the entire list and sets the head to NULL
/// @param head 
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

/// @brief clears the leftover input buffer
void clearInputBuffer ()
{
    char ch;
    // read until the end of the line or end of file
    while ((ch = getchar()) != '\n' && (int)ch != EOF);
}