/*
* Objective: Implement Queue using Stack
** Two stacks are needed: stack1 and stack2
** Stack1 is our main stack

** Enqueue function: add at the end of the queue
*** Pop all elements from stack1 and push them to stack2, one by one
*** This action will reverse the order of elements in stack1, which is now in stack2
*** Push the new element to stack1
*** Pop all elements from stack2 and push them to stack1, one by one
*** This effectively inserts the new element at the end of stack1

** Dequeue function: delete from the front of the queue
*** Pop the top element from stack1 and return it

* Note: Stack itself would be implemented using Linked List
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50

// Stack structure
typedef struct node
{
    int info;
    struct node *link;
} NODE;

// Queue structure
typedef struct queue
{
    NODE *stack1;
    NODE *stack2;
} QUEUE;


NODE *createNode (int data);
void push (NODE **top, int data);
int pop (NODE **top);
void printQueue (QUEUE q);
void enqueue (QUEUE *q, int data);
int dequeue (QUEUE *q);
bool isQueueEmpty (QUEUE *q);

int main ()
{
    int option, data;
    QUEUE q;
    q.stack1 = NULL;
    q.stack2 = NULL;

    do
    {
        printf("\n Queue operations:");
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display queue");
        printf("\n4. Exit");
        printf("\nEnter an option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                printf("\nEnter data to insert: ");
                scanf("%d", &data);
                enqueue(&q, data);
                printf("\n%d successfully inserted.", data);
                break;

            case 2:
                data = dequeue(&q);
                if (data != EOF)
                    printf("\nRemoved element: %d", data);
                else
                    printf("\nQueue is empty.");
                break;

            case 3:
                printQueue(q);
                break;

            case 4:
                printf("\nProgram exited.");
                break;

            default:
                printf("\nInvalid input. Please try again.");
                break;
        }
    } while (option != 4);
}

NODE *createNode (int data)
{
    NODE *newNode = (NODE *) malloc (sizeof (NODE));
    if (newNode == NULL)
    {
        printf ("Fatal Error: Memory allocation failed! \n");
        exit(EXIT_FAILURE);
    }
    newNode->info = data;
    newNode->link = NULL;
    return newNode;
}

void push (NODE **top, int data)
{
    NODE *newNode = createNode (data);
    newNode->link = *top;
    *top = newNode;
}

int pop (NODE **top)
{
    if (*top == NULL) // Stack is empty
        return EOF;
    NODE *temp = *top;
    int data = temp->info;
    *top = (*top)->link;
    free (temp);
    return data;
}

void printQueue (QUEUE q)
{
    // Pop each element from stack1 and push it to stack2, until stack1 is empty
    while (q.stack1 != NULL)
    {
        push(&q.stack2, pop(&q.stack1));
        printf("%d, ", q.stack2->info);
    }

    // Pop each element from stack2 and push it to stack1, until stack2 is empty
    while (q.stack2 != NULL)
    {
        push(&q.stack1, pop(&q.stack2));
    }
}

void enqueue (QUEUE *q, int data)
{
    // Pop each element from stack1 and push it to stack2, until stack1 is empty
    while (q->stack1 != NULL)
        push(&q->stack2, pop(&q->stack1));

    push(&q->stack1, data); // Push the new element to stack1

    // Pop each element from stack2 and push it to stack1, until stack2 is empty
    while (q->stack2 != NULL)
        push(&q->stack1, pop(&q->stack2));
}

int dequeue (QUEUE *q)
{
    return pop(&q->stack1);
}

bool isQueueEmpty (QUEUE *q)
{
    return (q->stack1 == NULL);
}