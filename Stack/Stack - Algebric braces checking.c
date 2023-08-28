/*
* Objective:
** Get a string containing brackets
** Check the string
*** Traverse each character from left to right
*** Ignore all other character except (), {}, []
*** If it is a opening brace push to stack\
*** the incoming opening brace should not be of higher priority than top of the stack
*** If it's a closing brace pop the top of the stack\
*** the top of the stack should be the corresponding closing brace
** Show the result
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100

typedef struct node
{
    char info;
    struct node *link;
} StackNode;

int priority (char ch);
void push (StackNode **top, char data);
char pop (StackNode **top);
char peek (StackNode *top);
bool isEmpty (StackNode *top);
bool isOpeningBrace (char ch);
bool isClosingBrace (char ch);
bool isValidExpression (char expression[]);

int main ()
{
    char expression[MAX_SIZE + 1];

    printf("Enter the expression with braces: ");
    fgets(expression, MAX_SIZE, stdin);

    if (isValidExpression(expression))
        printf("The braces in the expression are algebrically valid. \n");
    else
        printf("The expression contains invalid braces alignment. \n");
}

/// @brief Get the priority of the incoming character
/// @param ch is the incoming character, ideally a brace
/// @return returns the priority of the incoming character
int priority (char ch)
{
    switch (ch)
    {
        case '[':
        case ']':
            return 3;
        case '{':
        case '}':
            return 2;
        case '(':
        case ')':
            return 1;
        default:
            return -1;
    }
}

/// @brief Push function for stack implementation
/// @param top is the pointer to the top most element
/// @param data is the element to be pushed
void push (StackNode **top, char data)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Memory not allocated. \n");
        return;
    }
    newNode->info = data;
    newNode->link = *top;
    *top = newNode;
}

/// @brief Pop function for stack implementation
/// @param top is the pointer to the top most element
/// @return returns the popped element, EOF if stack is empty
char pop (StackNode **top)
{
    char data;
    StackNode *temp = *top;
    if (*top == NULL)
        return EOF;
    
    data = (*top)->info;
    (*top) = (*top)->link;

    free(temp);
    return data; 
}

/// @brief Peek function for stack implementation
/// @param top is the pointer to the top most element
/// @return returns the top most element (without removing it), EOF if stack is empty
char peek (StackNode *top)
{
    if (top == NULL)
        return EOF;
    return top->info;
}

/// @brief Check if the stack is empty
/// @param top is the pointer to the top most element
/// @return either true or false
bool isEmpty (StackNode *top)
{
    return (top == NULL);
}

/// @brief Check if the incoming character is a opening brace
/// @param ch is the incoming character
/// @return either true or false
bool isOpeningBrace (char ch)
{
    return (ch == '[' || ch == '{' || ch == '(');
}

/// @brief Check if ch is a closing brace
/// @param ch is the incoming character
/// @return either true or false
bool isClosingBrace (char ch)
{
    return (ch == ']' || ch == '}' || ch == ')');
}

/// @brief Checks whether the braces alignment in a given expression is valid
/// @param expression is the string containing the expression
/// @return either true or false
bool isValidExpression (char expression[])
{
    int i;
    char ch;
    StackNode *top = NULL;

    for (i = 0; expression[i] != '\0'; i++)
    {
        ch = expression[i];
        // if the incoming character is a opening brace
        if (isOpeningBrace(ch))
        {
            // if the stack is not empty
            // the priority of the incoming opening brace should be less than
            // the one in top of the stack
            if (isEmpty(top) || priority(ch) < priority(peek(top)))
                push(&top, ch);
            else
                return false;
        }
        // if the incoming character is a closing brace
        else if (isClosingBrace(ch))
        {
            // the top of the stack should correspond to the same opening brace
            if (priority(peek(top)) != priority(ch))
                return false;
            // if stack is empty instead, not valid
            if (pop(&top) == (char)EOF)
                return false;
        }
    }
    return isEmpty(top); // if stack is empty after all checking, valid
}