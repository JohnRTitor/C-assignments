#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int coeff;
    int expo;
    struct node *link;
} NODE;

NODE *createTerm (int coeff, int expo);
void sortedInsertTerm (NODE **head, int coeff, int expo);
void readPolynomial (NODE **head);
void printPolynomial (NODE *head);
NODE* addPolynomial (NODE *head1, NODE *head2);
NODE* multiplyPolynomial (NODE *head1, NODE *head2);

/*
int main ()
{
    int option;
    NODE *head = NULL, *head2 = NULL;
    NODE *sumHead = NULL, *productHead = NULL;

    while (true)
    {
        printf("** Main Menu ** \n");
        printf("1. Enter the two polynomials \n");
        printf("2. Print polynomials \n");
        printf("3. Add polynomials \n");
        printf("4. Multiply polynomials \n");
        printf("5. Delete the polynomials \n");

        printf("Enter an option: ");
        scanf("%d")
    }

}
*/

int main ()
{
    NODE *head1 = NULL, *head2 = NULL;

    readPolynomial(&head1);
    readPolynomial(&head2);
    printPolynomial(head1);
    printPolynomial(head2);

    printf("Add: \n");
    printPolynomial(addPolynomial(head1, head2));
    printf("Product: \n");
    printPolynomial(multiplyPolynomial(head1, head2));
    return 0;
}


/// @brief creates a polynomial term (NODE)
/// @param coeff is the coefficient for the new term
/// @param expo is x's exponent for the new term
/// @return the pointer to the newly created term
NODE *createTerm (int coeff, int expo)
{
    NODE *newTerm = (NODE *)malloc(sizeof(NODE));
    if (newTerm == NULL)
    {
        fprintf(stderr, "Fatal Error: Memory not allocated. \n");
        exit(-1);
    }
    newTerm->coeff = coeff;
    newTerm->expo = expo;
    newTerm->link = NULL;
    return newTerm;
}


/// @brief deletes the entire list and sets the head to NULL
/// @param head is the pointer to the head of the list, passed by reference
void freeList (NODE **head)
{
    NODE *temp = NULL;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->link;
        free(temp);
    }
}

/// @brief inserts a term in polynomial list, in descending order
/// @param head is the pointer to the first node
/// @param coeff is the coefficient for the new term
/// @param expo is x's exponent for the new term
/// @note precondition: the polynomial linked list needs to be sorted in descending order
void sortedInsertTerm (NODE **head, int coeff, int expo)
{
    NODE *newTerm = NULL;
    NODE *prev = NULL, *current = NULL;

    // terms with 0 coefficient should not be added
    if (coeff == 0)
        return;

    // create the node with the required exponent and x's coefficient
    newTerm = createTerm(coeff, expo);

    // if polynomial initially did not exist, so add as the first node
    if (*head == NULL)
    {
        *head = newTerm;
        return;
    }
    // if the newTerm is the largest by the x's power
    else if (newTerm->expo > (*head)->expo)
    {
        newTerm->link = *head;
        *head = newTerm;
        return;
    }
    
    // all other cases
    prev = NULL;
    current = *head;
    // traverse and find the ideal postion of insertion in descending order of exponent
    while (current != NULL && current->expo > newTerm->expo)
    {
        prev = current;
        current = current->link;
    }

    // the term is to be inserted at the last position
    if (current == NULL)
        prev->link = newTerm;
    // there is already one term with same x's exponent
    else if (current->expo == newTerm->expo)
    {
        // so add the coefficient's values together
        current->coeff += newTerm->coeff;
        free(newTerm); // list normalised, no need for this node
    }
    else
    {
        newTerm->link = current;
        prev->link = newTerm;
    }
}

/// @brief reads a polynomial expression from user input
/// @param head is the pointer to the first term, passed by reference
/// @note the polynomial expression is sorted in the descending order of x's exponents
void readPolynomial (NODE **head)
{
    int i, size;
    int coeff, expo;

    printf("Enter the no of terms: ");
    // get input, reprompt if invalid size is entered
    while (scanf("%d", &size) != 1 || size < 1);

    for (i = 1; i <= size; i++)
    {
        printf("Term #%d: \n", i);

        /*
        * read coefficient, and then x's expononent
        * if at any point, invalid input is given, reprompt
        */
        printf("Coefficient: ");
        while (scanf("%d", &coeff) != 1);

        printf("Exponent: ");
        while (scanf("%d", &expo) != 1);

        // inserts the term in descending order
        sortedInsertTerm(head, coeff, expo);
    }
}

/// @brief prints a polynomials terms: 3x^2 - 2x + 1 - 5^x-1
/// @param head is the pointer to the first term
void printPolynomial (NODE *head)
{
    NODE *current = NULL;
    if (head == NULL)
    {
        fprintf(stderr, "Error: Polynomial does not exist. \n");
        return;
    }

    for (current = head; current != NULL; current = current->link)
    {
        // if the term has a 0 coefficient, it should not be printed, skip it
        if (current->coeff == 0)
            continue;

        // print the + sign if the coefficient is positive and it's not the first term
        if (current->coeff > 0 && current != head)
            printf(" + ");
        // if the coefficient is negative instead, print - sign
        else if (current->coeff < 0)
            printf(" - ");

        // print the absolute value of the coefficient, as sign is taken care of by above
        // 1 should not be printed
        if (abs(current->coeff) != 1)
            printf("%d", abs(current->coeff));

        // if the exponent is 0, don't show the x term
        if (current->expo == 0)
            ; // print nothing
        // if x's exponent is 1
        else if (current->expo == 1)
            printf("x");
        // print with the exponent
        else
            printf("x^%d", current->expo);
        
    }
    printf("\n");
}

/// @brief adds two polynomials
/// @param head1 is the pointer to first polynomial
/// @param head2 is the pointer to second polynomial
/// @return the address of the sum polynomial
NODE* addPolynomial (NODE *head1, NODE *head2)
{
    NODE *newTerm = NULL;
    NODE *current1 = NULL, *current2 = NULL;
    NODE *sumHead = NULL, * sumCurrent = NULL;
    
    // merge polynomial 1 and polynomial 2
    current1 = head1;
    current2 = head2;
    while (current1 != NULL && current2 != NULL)
    {
        // polynomial1's term should go
        if (current1->expo > current2->expo)
        {
            newTerm = createTerm(current1->coeff, current1->coeff);
            current1 = current1->link;
        }
        // polynomial2's term should go
        else if (current2->expo > current1->expo)
        {
            newTerm = createTerm(current2->coeff, current2->coeff);
            current2 = current2->link;
        }
        // both term's exponent is same, so add them together
        else
        {
            newTerm = createTerm((current1->coeff + current2->coeff), current1->expo);
            current1 = current1->link;
            current2 = current2->link;
        }

        // now insert to the sum polynomial
        if (sumHead == NULL)
            sumHead = newTerm;
        else
            sumCurrent->link = newTerm;
        sumCurrent = newTerm;
    }
    
    // if first polynomial still has some term left
    while (current1 != NULL)
    {
        newTerm = createTerm(current1->coeff, current1->expo);
        sumCurrent->link = newTerm;
        sumCurrent = newTerm;
        current1 = current1->link;
    }

    // if the second polynomial still has some term left
    while (current2 != NULL)
    {
        newTerm = createTerm(current2->coeff, current2->expo);
        sumCurrent->link = newTerm;
        sumCurrent = newTerm;
        current2 = current2->link;
    }

    return sumHead;
}

/// @brief multiply two polynomials
/// @param head1 is the pointer to first polynomial
/// @param head2 is the pointer to second polynomial
/// @return the address of the product polynomial
NODE* multiplyPolynomial (NODE *head1, NODE *head2)
{
    NODE *newTerm = NULL;
    NODE *current1 = NULL, *current2 = NULL;
    NODE *productHead = NULL, *productCurrent = NULL;
    NODE *sortedProductHead = NULL;

    // multiplication is not possible
    if (head1 == NULL || head2 == NULL)
    {
        printf("Multiplication is not possible as one or both polynomials are empty. \n");
        return NULL;
    }
    
    for (current1 = head1; current1 != NULL; current1 = current1->link)
    {
        // multiply each term of polynomial1 with each term of polynomial2
        for (current2 = head2; current2 != NULL; current2 = current2->link)
        {
            // coefficients of the terms are multiplied
            // and exponents are summed
            newTerm = createTerm((current1->coeff * current2->coeff), (current1->expo + current2->expo));

            if (productHead == NULL)
                productHead = newTerm;
            else
                productCurrent->link = newTerm;
            productCurrent = newTerm;
        }
    }

	// normalise the terms by taking them one by one and sorted inserting them in a seperate polynomial linked list
	productCurrent = productHead;
	while (productCurrent != NULL)
	{
		sortedInsertTerm(&sortedProductHead, productCurrent->coeff, productCurrent->expo);
		productCurrent = productCurrent->link;
	}
    freeList(&productHead); // delete the old unsorted list
	return sortedProductHead;
}