#include <stdio.h>
#define MAX_SIZE 100
#define isFull(x) (x >= MAX_SIZE)
#define isEmpty(x) (x == -1)

typedef struct stack
{
	int element[MAX_SIZE];
	int top;
} STACK;
typedef struct queue
{
	int element[MAX_SIZE];
	int front;
	int rear;
} QUEUE;

void printStack (STACK s);
void push (STACK *s, int data);
int pop (STACK *s);
void reverseStack(STACK *s);
void enqueue (QUEUE *q, int data);
int dequeue (QUEUE *q);
void clearBuffer (void);

int main()
{
	STACK s;
	int option, data;
	
	s.top = -1; // initialise stack
	do
    {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Reverse\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);
        clearBuffer();
        
        switch (option)
        {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &data);
                push(&s, data);
                break;
            case 2:
                data = pop(&s);
                if (data != EOF)
                    printf("Popped element: %d\n", data);
                break;
            case 3:
            	reverseStack(&s);
                break;
            case 4:
            	printf("Stack is below:\n");
                printStack(s);
                break;
            case 5:
                printf("Program exited.\n");
                break;
            default:
                fprintf(stderr, "Invalid choice. Please try again.\n");
        }
    } while (option != 5);
    
    return 0;
}

void printStack (STACK s)
{
	int i;
	if (isEmpty(s.top))
	{
		fprintf(stderr, "Error: Stack is empty.\n");
		return;
	}
	for (i = s.top; i >= 0; i--) // print elements from top to bottom
	{
		printf("\t%d \n", s.element[i]);
	}
}

void push (STACK *s, int data)
{
	if (isFull(s->top))
	{
		fprintf(stderr, "Error: Stack is full.\n");
		return;
	}
	s->element[++(s->top)] = data; // increment stack->top by one and push the element
}

int pop (STACK *s)
{
	if (isEmpty(s->top))
		return EOF;
	return s->element[(s->top)--]; // return the top most element of the stack and remove it, by decrementing stack->top
}

void reverseStack (STACK *s)
{
	QUEUE q;
	// initialise queue
	q.front = -1;
	q.rear = -1;
	if (isEmpty(s->top))
	{
		fprintf(stderr, "Error: Stack is empty.");
		return;
	}
	while (!isEmpty(s->top)) // until stack is empty
	{
		enqueue(&q, pop(s)); // pop one element from the stack and add to queue
	}
	while (!isEmpty(q.front)) // until queue is empty
	{
		push(s, dequeue(&q)); // dequeue one element from the queue and push it to the stack
	}
	printf("Stack successfully reversed.");
}

void enqueue (QUEUE *q, int data)
{
	if (isFull(q->rear))
	{
		fprintf(stderr, "Error: Queue is full.\n");
		return;
	}
	if (isEmpty(q->front)) // if queue is initially empty, increment queue->front as well
		q->front = 0;
	q->element[++(q->rear)] = data; // increment queue->rear and add the element to at the end
}

int dequeue (QUEUE *q)
{
	int dequeued;
	if (isEmpty(q->front)) // queue is empty
		return EOF;
	
	dequeued = q->element[q->front]; // get the element to be dequeued
	if (q->front == q->rear) // only one element left
	{
		// update front and rear indicators to indicate the queue is fully empty
		q->front = -1;
		q->rear = -1;
	}
	else // there are multiple elements
		(q->front)++; // just increment the front indicator to mark dequeued
	return dequeued;
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}
