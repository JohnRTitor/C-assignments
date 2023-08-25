#include <stdio.h>
#include <stdlib.h>

typedef struct node // Define NODE structure
{
	int info;
	struct node *link;
} NODE;


NODE *createNode(int data);
void printStack (NODE *top);
void freeStack (NODE **top);
void push (NODE **top, int data);
int pop (NODE **top);
void reverseStack (NODE **top);
void clearBuffer (void);

int main()
{
	NODE *top = NULL;
	int option, data;
	
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
                push(&top, data);
                break;
            case 2:
                data = pop(&top);
                if (data != EOF)
                    printf("Popped element: %d\n", data);
                break;
            case 3:
            	printf("Before reversing: \n");
            	printStack(top);
            	printf("After reverse:\n");
            	reverseStack(&top);
				printStack(top);
                break;
            case 4:
            	printf("Stack is below:\n");
                printStack(top);
                break;
            case 5:
                printf("Program exited.\n");
                break;
            default:
                fprintf(stderr, "Invalid choice!\n");
        }
    } while (option != 5);
    
    freeStack(&top);
    return 0;
}

NODE *createNode (int data)
{
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		exit(-1);
	}
	newNode->info = data;
	newNode->link = NULL;
	return newNode;
}

void printStack (NODE *top)
{
	NODE *current;
	if (top == NULL)
	{
		fprintf(stderr, "Stack is empty.\n");
		return;
	}
	current = top;
	while (current != NULL)
	{
		printf("\t %d \n", current->info);
		current = current->link;
	}
}

void freeStack (NODE **top)
{
	while (*top != NULL)
		pop(top);
}

/* Pushes an element on the top of the stack */
void push (NODE **top, int data)
{
	NODE *temp = createNode(data);
	temp->link = *top;
	*top = temp;
}

/* Pop - removes the top element and returns it */
int pop (NODE **top)
{
	int data;
	NODE *temp;
	if (*top == NULL)
	{
		fprintf(stderr, "Error: Stack is empty.\n");
		return EOF;
	}
	temp = *top;
	data = (*top)->info;
	*top = (*top)->link;
	free(temp);
	return data;
}

void reverseStack (NODE **top)
{
	int data;
	NODE *tempTop = NULL;
	while (*top != NULL)
	{
		data = pop(top);
		if (data != EOF)
			push(&tempTop, data);
	}
	*top = tempTop;
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}