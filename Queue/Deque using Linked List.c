#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int info;
	struct node *link;
} NODE;
typedef struct deque
{
	NODE *front;
	NODE *rear;
} DEQUE;

typedef enum state
{
	input=1,
	output=0
} STATE;

NODE *createNode (int data);
void printDeque (DEQUE);
void eraseDeque (DEQUE *);
void enqueue (DEQUE *, int, STATE);
int dequeue (DEQUE *, STATE);
void clearBuffer (void);

int main ()
{
	DEQUE q;
	int option, data;
	// input restricted by default 
	char mode[7] = "input";
	STATE restriction = input;
	// queue initialisation
	q.front = NULL;
	q.rear = NULL;
	
	do
    {
        printf("\nDeque (Double-Ended Queue) operations: \n");
        printf("0. Change restriction (current: %s)\n", mode);
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Deque\n");
        printf("4. Erase Deque\n");
        printf("5. Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option)
        {
            case 0:
        		printf("Press 1 for input restriction, or any key for output restricted mode: ");
        		restriction = (getchar() == '1') ? input : output;
        		strcpy(mode, ((restriction == input) ? "input" : "output"));
        		clearBuffer();
        		break;
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                clearBuffer();
                enqueue(&q, data, restriction);
                printf("%d successfully inserted.\n", data);
                break;

            case 2:
                data = dequeue(&q, restriction);
                if (data != EOF)
                {
                    printf("Removed element: %d\n", data);
                }
                break;

            case 3:
                printDeque(q);
                break;

            case 4:
            	eraseDeque(&q);
            	printf("Completely deleted the whole Deque. Please start over!\n");
            	break;
            case 5:
                printf("Program exited.\n");
                break;

            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    } while (option != 5);
    eraseDeque(&q);
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

void printDeque (DEQUE q)
{
	NODE *current;
	if (q.front == NULL || q.rear == NULL)
	{
		fprintf(stderr, "Error: Deque is empty.\n");
		return;
	}
	current = q.front;
	while (current != NULL)
	{
		printf("%d, ", current->info);
		current = current->link;
	}
}

void eraseDeque (DEQUE *q)
{
	NODE *temp;
	NODE *current = q->front;
	while (current != NULL)
	{
		temp = current;
		current = current->link;
		free(temp);
	}
	q->front = NULL;
	q->rear = NULL;
}

void enqueue (DEQUE *q, int data, STATE restriction)
{
	enum {front, rear}option;
	NODE *newNode = createNode(data);
	if (newNode == NULL) // insufficient memory
	{
		fprintf(stderr, "Error: No space left in Deque.\n");
		return;
	}
	if (q->front == NULL || q->rear == NULL) // Deque is empty
	{
		q->front = newNode;
		q->rear = newNode;
		return;
	}
	option = rear; // default value for enqueue
	if (restriction != input)
	{
		printf("Enter 1 for enqueuing in front, or press any key for rear enqueuing (default): ");
		option = (getchar() == '1') ? front : rear;
	}
	
	if (restriction != input && option == front) // front insertion
	{
		newNode->link = q->front;
		q->front = newNode;
	}
	else // rear insertion (default)
	{
		(q->rear)->link = newNode;
		q->rear = (q->rear)->link;
	}
}

int dequeue (DEQUE *q, STATE restriction)
{
	enum {front, rear}option;
	NODE *temp;
	int data;
	if (q->front == NULL)
	{
		fprintf(stderr, "Error: Deque is empty.\n");
		return EOF;
	}

	data = (q->front)->info;
	if (q->front == q->rear) // there is only one element
	{
		free(q->front);
		q->front = NULL;
		q->rear = NULL;
		return data;
	}
	// multiple elements present
	option = rear; // default rear deletion
	if (restriction != output)
	{
		printf("Enter 1 for deletion from rear end, or press any key for front deletion (default): ");
		option = (getchar() == '1') ? rear : front;
	}
	
	if (restriction != output && option == rear) // rear end deletion
	{
		data = (q->rear)->info; // get the last node's value
		temp = q->front;
		// traverse to the node before the last node
		while (temp->link != q->rear)
		{
			temp = temp->link;
		}
		free(q->rear);
		q->rear = temp;
		(q->rear)->link = NULL;
	}
	else // front deletion (default)
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
