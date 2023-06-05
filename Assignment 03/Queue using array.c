#include <stdio.h>
#define MAX_SIZE 40

typedef struct queue
{
	int element[MAX_SIZE];
	int front;
	int rear;
} QUEUE;

void printQueue (QUEUE);
void enqueue (QUEUE *, int);
int dequeue (QUEUE *);

int main ()
{
	QUEUE q;
	int option, data;
	q.front = -1;
	q.rear = -1;
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

void printQueue (QUEUE q)
{
	int i;
	if (q.front == -1 || q.rear == -1)
	{
		fprintf(stderr, "Error: Queue is empty.");
		return;
	}
	for (i = q.front; i <= q.rear; i++)
	{
		printf("%d, ", q.element[i]);
	}
}

void enqueue (QUEUE *q, int data)
{
	if (q->rear == MAX_SIZE - 1) // queue is full
	{
		fprintf(stderr, "Error: No space left in queue.");
		return;
	}
	if (q->front == -1 && q->rear == -1) // queue is empty
	{
		q->front = 0;
	}
	(q->rear)++;
	q->element[q->rear] = data;
}

int dequeue (QUEUE *q)
{
	int data;
	if (q->front == -1)
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
	{
		(q->front)++;
	}
	return data;
}