#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

void printStack(int stack[], int top);
void push(int stack[], int *top, int data);
int pop (int stack[], int *top);
void reverseStack (int *stack[], int *top);
void clearBuffer (void);

int main()
{
	int *stack = NULL, top = -1;
	int option, data;
	
	stack = (int *)calloc(MAX_SIZE, sizeof(int));
	if (stack == NULL)
	{
		fprintf(stderr, "Error: Memory not allocated.");
		exit(-1);
	}
	
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
                push(stack, &top, data);
                break;
            case 2:
                data = pop(stack, &top);
                if (data != EOF)
                    printf("Popped element: %d\n", data);
                break;
            case 3:
            	printf("Before reversing: \n");
            	printStack(stack, top);
            	printf("After reverse:\n");
            	reverseStack(&stack, &top);
				printStack(stack, top);
                break;
            case 4:
            	printf("Stack is below:\n");
                printStack(stack, top);
                break;
            case 5:
                printf("Program exited.\n");
                break;
            default:
                fprintf(stderr, "Invalid choice. Please try again.\n");
        }
    } while (option != 5);
    
    free(stack);
    return 0;
}

void printStack (int stack[], int top)
{
	int i;
	if (top <= -1)
	{
		fprintf(stderr, "Error: Stack is empty.");
		return;
	}
	for (i = top; i >= 0; i--) // print elements from top to bottom
	{
		printf("%d \n", stack[i]);
	}
}

void push(int stack[], int *top, int data) // pushes an element onto top of a stack
{
	if (*top >= MAX_SIZE - 1) // if full, the element can't be pushed
	{
		fprintf(stderr, "Error: Stack overflow!");
		return;
	}
	(*top)++;
	stack[*top] = data;
}

int pop (int stack[], int *top) // removes the top element and returns it
{
	int data;
	if (*top <= -1) // if stack is empty, return EOF
	{
		fprintf(stderr, "Error: Stack is empty.");
		return EOF;
	}
	data = stack[*top];
	(*top)--; // decrement top by 1
	return data;
}

void reverseStack (int *stack[], int *top)
{
	int *tempStack = NULL, tempTop;
	int data;
	
	if (*top <= -1)
	{
		fprintf(stderr, "Error: Stack is empty.");
		return;
	}
	
	tempStack = (int *)calloc(MAX_SIZE, sizeof(int));
	if (tempStack == NULL)
	{
		fprintf(stderr, "Error: Memory not allocated.");
		return;
	}
	
	tempTop = -1;
	while (*top > -1) // until source stack becomes empty
	{
		data = pop(*stack, top); // pop the source stack
		push(tempStack, &tempTop, data); // push the popped item to the auxiliary stack
	}
	
	free(*stack); // clean up the memory occupied by source stack
	*stack = tempStack; // copy the auxiliary stack to source stack
	*top = tempTop; // copy the top pointer value as well, stack is now reversed
}

void clearBuffer (void) // clears input buffer
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discards leftover characters in the input stream
}