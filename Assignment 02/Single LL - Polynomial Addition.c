#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adds two polynomials

typedef struct polTerm
{
	int coeff;
	int exp;
	struct polTerm *link;
} POL;

POL* createTerm(int coefficient, int exponent);
void readPolynomial (POL **head);
void printPolynomial (POL *head);
void freePolynomial(POL* head);
void addPolynomial (POL *f, POL *g, POL **sum);
void normalisePolynomial (POL *head);
void bubbleSortPolDec (POL *head);
void swap (int *x, int *y);

int main()
{
	POL *f, *g, *sum;
	
	// reads f(x) and g(x) stores to f and g respectively
	printf("Enter f(x):\n");
	readPolynomial(&f);
	printf("\nEnter g(x):\n");
	readPolynomial(&g);
	
	printf("\n f(x) = ");
	printPolynomial(f->link);
	printf(" = ");
	normalisePolynomial(f->link);
	printPolynomial(f->link);
	
	printf("\n g(x) = ");
	printPolynomial(g->link);
	printf(" = ");
	normalisePolynomial(g->link);
	printPolynomial(g->link);
	
	printf("\n Sum = f(x) + g(x) = ");
	addPolynomial(f, g, &sum);
	printPolynomial(sum->link);
	
	freePolynomial(f), freePolynomial(g), freePolynomial(sum);
	return 0;
}

POL* createTerm (int coefficient, int exponent)
{
	POL *newTerm = (POL *)malloc(sizeof(POL));
	if (newTerm == NULL)
	{
		fprintf(stderr, "\nError: Memory allocation failed.\n");
		exit(-1);
	}
	newTerm->coeff = coefficient;
	newTerm->exp = exponent;
	newTerm->link = NULL;
	return newTerm;
}

void readPolynomial (POL **head)
{
	POL temp, *ptr;
	int i, noOfTerms;
	*head = createTerm(0, 0); // empty header node
	printf("Enter the no of terms:");
	scanf("%d", &noOfTerms);
	if (head == 0 || noOfTerms < 1)
	{
		fprintf(stderr, "Error: Invalid size. List can not be made.");
		exit(-1);
	}
	ptr = *head;
	for (i = 1; i <= noOfTerms; i++)
	{
		printf("\nEnter term#%d:", i);
		printf("\n\tCoefficient:");
		scanf("%d", &temp.coeff);
		printf("\tDegree of x term:");
		scanf("%d", &temp.exp);
		ptr->link = createTerm(temp.coeff, temp.exp);
		ptr = ptr->link;
	}
}

void printPolynomial (POL *head)
{
	POL *ptr = head;
	if (head == NULL)
	{
		fprintf(stderr, "\nPolynomial does not exist.\n");
		return;
	}
	if (ptr->link == NULL && ptr->coeff == 0) // for a polynomial with only one member that is 0
	{
		printf(" 0 ");
		return;
	}
	while (ptr != NULL)
	{
		if (ptr != head && ptr->coeff > 0) // if it is not the first term and coefficient is positive
		{
			printf(" + ");
		}
		else if (ptr->coeff < 0) // if coefficient is negative
		{
			printf(" - ");
		}
		if (ptr->coeff != 0 && ptr->coeff != 1) // prints the absolute value of coefficient
		{
			printf("%d", abs(ptr->coeff));
		}
		if (ptr->exp != 0 && ptr->coeff != 0) // prints the x term
		{
			printf("x");
			if (ptr->exp != 1) // include the exponent if needed
			{
				printf("^%d", ptr->exp);
			}
		}
		ptr = ptr->link;
	}
}

void freePolynomial(POL* head) // frees the entire Polynomial storage
{
    POL *current, *temp;
    current = head;
    while (current != NULL)
    {
        temp = current;
        current = current->link;
        free(temp);
    }
}

void addPolynomial (POL *f, POL *g, POL **sum) // creates nodes for sum and stores the result of f+g
{
	POL *ptr, *sumPtr;
	
	if (f == NULL && g == NULL)
	{
		fprintf(stderr, "Addition of f(x) and g(x) is not possible.");
		return;
	}
	
	*sum = createTerm(0, 0); // create header node for polynomial sum
	
	sumPtr = *sum;
	ptr = f;
	while (ptr != NULL) // copies f polynomial terms to sum
	{
		sumPtr->link = createTerm(ptr->coeff, ptr->exp);
		sumPtr = sumPtr->link;
		ptr = ptr->link;
	}
	
	ptr = g;
	while (ptr != NULL) // appends g polynomial terms to sum
	{
		sumPtr->link = createTerm(ptr->coeff, ptr->exp);
		sumPtr = sumPtr->link;
		ptr = ptr->link;
	}
	
	// f and g successfully merged, now normalise
	normalisePolynomial((*sum)->link);
	// normalising collects coefficients of similar terms (with same exponents of x)
}

/* Normalise a polynomial, the terms with the same exponent will be merged into a single term with the combined coefficient */
void normalisePolynomial(POL *head)
{
    POL *currentTerm, *compareTerm, *prevCompareTerm;
    
    if (head == NULL)
    {
    	fprintf(stderr, "Error: List is empty.");
    	return;
    }
    if (head->link == NULL)
    {
    	return; // there is only one term, so no need to normalise
    }
    
    bubbleSortPolDec(head); // first sort the polynomial into decreasing order of exponents
    
    currentTerm = head; // start from the beginning of the list
    while (currentTerm != NULL)
    {
        /* start comparing with the next term, a pointer to the previous term should be maintained for deletion in case exponents are the same */
        prevCompareTerm = currentTerm;
        compareTerm = currentTerm->link;
        while (compareTerm != NULL)
        {
            if (currentTerm->exp == compareTerm->exp)
            {
                currentTerm->coeff += compareTerm->coeff; // add the coefficient to the currentTerm
                // Delete the compareTerm node by updating the prevCompareTerm pointer to skip over compareTerm in the linked list
                prevCompareTerm->link = compareTerm->link;
                free(compareTerm); // free the memory associated with compareTerm
                compareTerm = prevCompareTerm->link; // move the pointer after the one that was deleted
            }
            else // move both pointers one step forward
            {
                prevCompareTerm = compareTerm;
                compareTerm = compareTerm->link;
            }
        }
        currentTerm = currentTerm->link; // go to the next term
    }
}

/* Sorts the Polynomial is descending order of x's exponent */
void bubbleSortPolDec (POL *head)
{
	POL *ptr, *current, *next;
	int swapped;
	POL *lastSwapped;
	
	if (head == NULL)
	{
		fprintf(stderr, "Error: List is empty.");
		return;
	}
	
	ptr = head; // just used to iterate n-1 times, this has no other use
	lastSwapped = NULL; // used to mark the sorted portion of list
	while (ptr->link != NULL) // pass loop
	{
		swapped = false; // initially set to false, used to check if a swap has been performed
		current = head; // set current to the first node
		while (current->link != lastSwapped) // comparison loop, until sorted portion appears
		{
			next = current->link; // next node of current
			if (current->exp < next->exp) // compare and start swapping so smallest degree ends up at the last
			{
				swap(&current->exp, &next->exp);
				swap(&current->coeff, &next->coeff);
				swapped = true;
			}
			current = current->link; // move current one step forward
		}
		lastSwapped = current; // sorted portion starts
		if (swapped == false) // no swap occurred in the pass, so list is already sorted
		{
			break;
		}
		ptr = ptr->link;
	}
}

void swap (int *x, int *y) // swaps two integers
{
	int temp = *x;
	*x = *y;
	*y = temp;
}