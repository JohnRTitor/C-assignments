#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int info;
	struct node *link;
} NODE;
typedef struct queue
{
	NODE *front;
	NODE *rear;
} QUEUE;

NODE *createNode(int data);
void printQueue (QUEUE);
void freeQueue (QUEUE);
void enqueue (QUEUE *, int);
int dequeue (QUEUE *);
void clearBuffer (void);

int main ()
{
	QUEUE q;
	int option, data;
	q.front = NULL;
	q.rear = NULL;
	do
    {
        printf("\n Queue operations:");
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
    freeQueue(q);
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

void printQueue (QUEUE q)
{
	NODE *current;
	if (q.front == NULL || q.rear == NULL)
	{
		fprintf(stderr, "Error: Queue is empty.");
		return;
	}
	current = q.front;
	while (current != NULL)
	{
		printf("%d, ", current->info);
		current = current->link;
	}
}

void freeQueue (QUEUE q)
{
	NODE *temp;
	NODE *current = q.front;
	while (current != NULL)
	{
		temp = current;
		current = current->link;
		free(temp);
	}
}

void enqueue (QUEUE *q, int data)
{
	NODE *newNode = createNode(data);
	if (newNode == NULL) // insufficient memory
	{
		fprintf(stderr, "Error: No space left in queue.");
		return;
	}
	if (q->front == NULL || q->rear == NULL) // queue is empty
	{
		q->front = newNode;
		q->rear = newNode;
		return;
	}
	(q->rear)->link = newNode;
	q->rear = (q->rear)->link;
}

int dequeue (QUEUE *q)
{
	NODE *temp;
	int data;
	if (q->front == NULL)
	{
		fprintf(stderr, "Error: Queue is empty.");
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
		free(temp);
	}
	return data;
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}