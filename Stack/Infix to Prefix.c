#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

#define isOperator(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
#define isOperand(c) (isalnum(c))

void push(char stack[], int *top, char data);
char pop(char stack[], int *top);
void xstrrev (char str[]);
int precedence(char ch);
int isValidExpression(char expression[]);
void infixToPrefix(char infix[], char prefix[]);

int main()
{
	char infix[MAX_SIZE], prefix[MAX_SIZE];
	printf("Enter an infix expression: ");
	while (fgets(infix, MAX_SIZE, stdin) == NULL || infix[0] == '\n');
	infix[strlen(infix) - 1] = '\0';

	if (!isValidExpression(infix))
	{
		printf("Invalid infix expression.");
		return EXIT_FAILURE;
	}
	printf("The prefix expression is: ");
	
	infixToPrefix(infix, prefix);
	puts(prefix);

	return EXIT_SUCCESS;
}


void push(char stack[], int *top, char data) // pushes an element onto top of a stack
{
	stack[++(*top)] = data;
}

char pop(char stack[], int *top) // removes the top element and returns it
{
	if (*top <= -1) // if stack is empty, return EOF
	{
		return EOF;
	}
	return stack[(*top)--]; // remove the top element and decrement top by one
}

int precedence(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}

int isValidExpression(char expression[])
{
	int i, top = -1;
	char stack[MAX_SIZE];
	
	for (i = 0; expression[i] != '\0'; i++)
	{
		if (isspace(expression[i])) // skip all whitespace
			continue;
		else if (isOperand(expression[i]) || isOperator(expression[i]))
			continue;
		else if ('(' == expression[i])
			push(stack, &top, expression[i]);
		else if (')' == expression[i])
		{
			if (pop(stack, &top) == (char)EOF) // if stack there is no opening parantheses in the stack
				return false;
		}
		else
			return false;
	}

	if (top != -1)
		return false;

	return true;
}

void infixToPrefix(char infix[], char prefix[])
{
	char ch;
	int i, j, top = -1;
	char stack[MAX_SIZE];
	
	// traverse the infix expression from right to left
	for (i = strlen(infix)-1, j = 0; i >= 0; i--)
	{
		ch = infix[i];					  // read a character from infix expression
		if (isOperand(ch) || isspace(ch)) // operand is found, add to output string
			prefix[j++] = ch;
		else if (ch == ')') // closing parantheses is found, push into the stack
			push(stack, &top, ch);
		else if (ch == '(')
		{
			while (stack[top] != ')') // pop all operators until '(' is found
				pop(stack, &top);
			pop(stack, &top); // pop ')' too
		}
		else // operator is encountered
		{
			while (top != -1 && precedence(ch) < precedence(stack[top])) // pop operators in the stack until a lower priority operator found
				prefix[j++] = pop(stack, &top);
			push(stack, &top, ch); // then push the operator
		}
	}

	// The expression fully traversed but stack is not empty yet
	while (top != -1)
		prefix[j++] = pop(stack, &top);
	prefix[j] = '\0'; // make it a valid string
	
	xstrrev(prefix); // reverse the expression again to get the final result
}

void xstrrev (char str[])
{
	int i, j;
	char temp;
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}