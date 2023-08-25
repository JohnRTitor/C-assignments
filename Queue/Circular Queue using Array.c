#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 40

typedef struct cqueue
{
	int element[MAX_SIZE];
	int front;
	int rear;
} CQUEUE;

bool isEmpty (CQUEUE *);
bool isFull (CQUEUE *);
void printQueue (CQUEUE);
void enqueue (CQUEUE *, int);
int dequeue (CQUEUE *);

int main ()
{
	CQUEUE q;
	int option, data;
	
	q.front = -1;
	q.rear = -1;
	
	do
    {
        printf("\nCircular Queue operations:");
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
                {
                    printf("\nRemoved element: %d", data);
                }
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
	return 0;
}

bool isEmpty (CQUEUE *q)
{
    return (q->front == -1 && q->rear == -1);
}

bool isFull (CQUEUE *q)
{
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

void printQueue (CQUEUE q)
{
	int i;
	if (isEmpty(&q))
	{
		fprintf(stderr, "Error: Queue is empty.");
		return;
	}
	i = q.front;
	while (i <= q.rear)
	{
		printf("%d, ", q.element[i]);
		i = (i + 1) % MAX_SIZE;
	}
}

void enqueue (CQUEUE *q, int data)
{
	if (isFull(q))
	{
		fprintf(stderr, "Error: No space left in queue.");
		return;
	}
	if (isEmpty(q)) // queue is empty
	{
		q->front = 0;
		q->rear = 0;
	}
	else
		q->rear = (q->rear + 1) % MAX_SIZE;
	q->element[q->rear] = data;
}

int dequeue (CQUEUE *q)
{
	int data;
	if (isEmpty(q))
	{
		fprintf(stderr, "Error: Queue is empty.");
		return EOF;
	}
	
	data = q->element[q->front];
	if (q->front == q->rear) // there is only one element
	{
		q->front = -1;
		q->rear = -1;
	}
	else // multiple elements present
		q->front = (q->front + 1) % MAX_SIZE;
	return data;
}