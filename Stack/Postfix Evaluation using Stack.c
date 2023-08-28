#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE 1000

#define isOperand(c) (isdigit(c))

void push(int stack[], int *top, int data);
int pop(int stack[], int *top);
int evaluatePostfix(char postfix[]);

int main()
{
	int result;
	char postfix[MAX_SIZE];

	printf("Enter a postfix expression to evaluate: ");
	while(fgets(postfix, MAX_SIZE, stdin) == NULL || postfix[0] == '\n'); // while loop to check for accidental enter press
	postfix[strlen(postfix) - 1] = '\0'; // discard the trailing \n character 
	
	result = evaluatePostfix(postfix);

	printf("The postfix expression: %s.\n", postfix);
	printf("Evaluated to %d.", result);
	
	return EXIT_SUCCESS;
}

void push(int stack[], int *top, int data) // pushes an element onto top of a stack
{
	stack[++(*top)] = data;
}

int pop(int stack[], int *top) // removes the top element and returns it
{
	if (*top <= -1) // if stack is empty, return EOF
		return EOF;
	return stack[(*top)--]; // remove the top element and decrement top by one
}

int evaluatePostfix(char postfix[]) // evaluates a postfix notation and returns the calculated result
{
	char ch;
	int x, y, result;
	int i, top = -1;
	int stack[MAX_SIZE];

	for (i = 0; postfix[i] != '\0'; i++)
	{
		ch = postfix[i]; // read a character from postfix expression
		if (isspace(ch)) // skip spaces
			continue;
		else if (isOperand(ch))
			push(stack, &top, ch - '0'); // convert char digit to int and push to stack
		else
		{
			// since y is stored on top of x
			y = pop(stack, &top);
			x = pop(stack, &top);
			// calculates result based on the incoming operator
			switch (ch)
			{
				case '+':
					result = x + y;
					break;
				case '-':
					result = x - y;
					break;
				case '*':
					result = x * y;
					break;
				case '/':
					if (y == 0)
					{
						fprintf(stderr, "Division by zero is not possible.");
						exit(1);
					}
					result = x / y;
					break;
				case '^':
					result = pow(x, y);
					break;
				default:
					printf("Invalid operator: %c", ch);
					exit(1);
			}
			push(stack, &top, result); // push the calculation result to stack
		}
	}
	return pop(stack, &top); // pop the result at the end return it
}
