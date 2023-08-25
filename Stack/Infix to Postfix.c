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
int precedence(char ch);
int isValidExpression(char expression[]);
void infixToPostfix(char infix[], char postfix[]);

int main()
{
	char infix[MAX_SIZE], postfix[MAX_SIZE];
	printf("Enter an infix expression: ");
	while(fgets(infix, MAX_SIZE, stdin) == NULL || infix[0] == '\n');
	infix[strlen(infix) - 1] = '\0';
	

	if (!isValidExpression(infix))
	{
		printf("Invalid infix expression.");
		free(infix);
		return EXIT_FAILURE;
	}
	printf("The postfix expression is: ");
	
	infixToPostfix(infix, postfix);
	puts(postfix);

	return EXIT_SUCCESS;
}


void push(char stack[], int *top, char data) // pushes an element onto top of a stack
{
	stack[++(*top)] = data;
}

char pop(char stack[], int *top) // removes the top element and returns it
{
	if (*top <= -1) // if stack is empty, return EOF
		return EOF;
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

void infixToPostfix(char infix[], char postfix[])
{
	char ch;
	int i, j, top = -1;
	char stack[MAX_SIZE];

	for (i = j = 0; infix[i] != '\0'; i++)
	{
		ch = infix[i];					  // read a character from infixexpression
		if (isOperand(ch) || isspace(ch)) // operand is found, add to output string
			postfix[j++] = ch;
		else if (ch == '(') // opening parantheses is found, push into the stack
			push(stack, &top, ch);
		else if (ch == ')')
		{
			while (stack[top] != '(') // pop all operators until '(' is found
				pop(stack, &top);
			pop(stack, &top); // pop '(' too
		}
		else // operator is encountered
		{
			while (top != -1 && precedence(ch) <= precedence(stack[top])) // pop operators in the stack until a lower priority operator found
				postfix[j++] = pop(stack, &top);
			push(stack, &top, ch); // then push the operator
		}
	}

	// The expression fully traversed but stack is not empty yet
	while (top != -1)
		postfix[j++] = pop(stack, &top);
	postfix[j] = '\0'; // make it a valid string
}
