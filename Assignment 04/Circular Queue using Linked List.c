#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int info;
	struct node *link;
} NODE;
typedef struct circularQueue
{
	NODE *front;
	NODE *rear;
} CQUEUE;

NODE *createNode(int data);
void printQueue (CQUEUE);
void freeCQueue (CQUEUE *);
void enqueue (CQUEUE *, int);
int dequeue (CQUEUE *);
void clearBuffer (void);

int main ()
{
	CQUEUE q;
	int option, data;
	
	q.front = NULL;
	q.rear = NULL;
	
	do
    {
        printf("\nCircular Queue operations:");
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display queue");
        printf("\n4. Exit");
        printf("\nEnter an option: ");
        scanf("%d", &option);
        clearBuffer();

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
    freeCQueue(&q);
	return 0;
}

NODE *createNode(int data)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return NULL;
	}
	newNode->info = data;
	newNode->link = NULL;
	return newNode;
}

void printQueue (CQUEUE q)
{
	NODE *current;
	if (q.front == NULL || q.rear == NULL)
	{
		fprintf(stderr, "Error: Circular Queue is empty.");
		return;
	}
	current = q.front;
	do
	{
		printf("%d, ", current->info);
		current = current->link;
	} while (current != q.front);
}

void freeCQueue (CQUEUE *q)
{
	NODE *temp;
	NODE *current = q->front;
	do
	{
		temp = current;
		current = current->link;
		free(temp);
	} while (current != q->front);
}

void enqueue (CQUEUE *q, int data)
{
	NODE *newNode = createNode(data);
	if (newNode == NULL) // insufficient memory
	{
		fprintf(stderr, "Error: No space left in circular queue.");
		return;
	}
	
	if (q->front == NULL && q->rear == NULL) // queue is empty
	{
		q->front = newNode;
		q->rear = newNode;
	}
	else
	{
		(q->rear)->link = newNode;
		q->rear = (q->rear)->link;
	}
	(q->rear)->link = q->front; // make it circular
}

int dequeue (CQUEUE *q)
{
	NODE *temp;
	int data;
	if (q->front == NULL)
	{
		fprintf(stderr, "Error: Circular Queue is empty.");
		return EOF;
	}

	data = (q->front)->info;
	if (q->front == q->rear) // there is only one element
	{
		free(q->front);
		q->front = NULL;
		q->rear = NULL;
	}
	else // multiple elements present
	{
		temp = q->front;
		q->front = (q->front)->link;
		(q->rear)->link = q->front; // make it circular
		free(temp);
	}
	return data;
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}