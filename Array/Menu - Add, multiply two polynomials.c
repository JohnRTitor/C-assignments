#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX_DEG 30

/* Program reads two polynomials, f(x) and g(x), presents a menu, performs addition or multiplication as per option */

typedef struct polynomial
{
	int highestDeg;
	double coeff[MAX_DEG + 1]; // to include the const term
} POL;

int readPolynomial(POL *);
void printPolynomial(const POL);
void addPolynomial(const POL, const POL, POL *);
void multiplyPolynomial(const POL, const POL, POL *);
void clearBuffer();
void zeroInitialise(POL *);

int main()
{
	POL f, g, sum, product;
	int option;

	printf("Enter f(x):");
	while (readPolynomial(&f) != true); // this recalls the function again in case of invalid input
	printf("\nEnter g(x):");
	while (readPolynomial(&g) != true);

	while (true)
	{
		printf("\nDo operations on f(x) and g(x). \n\t Press '1' for addition. \n\t Press '2' for multiplication. \n\t Press '3' to reenter f(x) and g(x). \n\t Press '4' to display f and g. \n\t Press '5' to exit. \nEnter an option:");
		scanf("%d", &option);
		if (option == 5)
		{
			printf("\nProgram exited.");
			break;
		}
		clearBuffer();
		switch (option)
		{
		case 1:
			addPolynomial(f, g, &sum);
			printf("\nAddition of f(x) and g(x) is successful. Below is the result:\n");
			printPolynomial(sum);
			break;
		case 2:
			multiplyPolynomial(f, g, &product);
			printf("\nMultiplication of f(x) and g(x) is successful. Below is the result:\n");
			printPolynomial(product);
			break;
		case 3:
			printf("\nEnter f(x):\n");
			while (readPolynomial(&f) != true);
			printf("\nEnter g(x):\n");
			while (readPolynomial(&g) != true);
			break;
		case 4:
			printf("\nf(x) = ");
			printPolynomial(f);
			printf("\ng(x) = ");
			printPolynomial(g);
			break;
		default:
			fprintf(stderr, "\nInvalid input. Please try again.");
		}
	}

	return 0;
}

/* Returns false when fails to read input for polynomial p, true if successful */
int readPolynomial(POL *p)
{
	int i;
	zeroInitialise(p); // initialise all values to 0
	printf("\n\tEnter the highest degree:");

	if (scanf("%d", &p->highestDeg) != 1 || p->highestDeg < 0)
	{
		fprintf(stderr, "Please enter only positive values upto %d!", MAX_DEG);
		clearBuffer();
		return false;
	}
	for (i = (p->highestDeg); i >=0 ; i--)
	{
		printf("\tEnter the coeff of x^%d:", i);
		if (scanf("%lf", &p->coeff[i]) != 1)
		{
			fprintf(stderr, "\tInvalid input. Please try again!");
			i++; // this initiates the loop again
		}
		clearBuffer();
	}
	return true;
}

/* Prints polynomial p like this: 2.30x^2 + 5.5x + 8.9 */
void printPolynomial(const POL p)
{
	int i;
	for (i = p.highestDeg; i >= 0; i--)
	{
		if (i < p.highestDeg && p.coeff[i] > 0) // the term is not the first and coefficient is greater than 0
		{
			printf(" + ");
		}
		else if (p.coeff[i] < 0) // if the term's coefficient is less than 0
		{
			printf(" - ");
		}
		if (p.coeff[i] != 0)
		{
			printf("%.2lf", fabs(p.coeff[i])); // get the absolute value of the coefficent
		}
		if (i > 1)
		{
			printf("x^%d", i);
		}
		else if (i == 1)
		{
			printf("x");
		}
	}
}

/* Calculates f+g and stores in res */
void addPolynomial(const POL f, const POL g, POL *res)
{
	int i;
	zeroInitialise(res); // initialise all values to 0

	(res->highestDeg) = (f.highestDeg > g.highestDeg) ? f.highestDeg : g.highestDeg; // resultant's highest degree is f or g's highest degree, whichever is larger

	for (i = 0; i <= f.highestDeg || i <= g.highestDeg; i++)
	{
		(res->coeff[i]) = f.coeff[i] + g.coeff[i]; // add the coeff of similar terms
	}
}

/* Calculates fXg and stores in res */
void multiplyPolynomial(const POL f, const POL g, POL *res)
{
	int i, j;
	zeroInitialise(res);
	(res->highestDeg) = f.highestDeg + g.highestDeg; // highest degree of resultant is the sum of the polynomials' highest degree

	for (i = 0; i <= f.highestDeg; i++)
	{
		for (j = 0; j <= g.highestDeg; j++)
		{
			(res->coeff[i + j]) += f.coeff[i] * g.coeff[j]; // multiply and collect the similar terms
		}
	}
}

/* Clears input buffer */
void clearBuffer(void)
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discard leftover characters in the input stream until \n or EOF is encountered
}

/* Initialises a whole POL variable to 0 */ 
void zeroInitialise(POL *p)
{
	int i;
	(p->highestDeg) = 0;
	for (i = 0; i <= MAX_DEG; i++)
	{
		(p->coeff[i]) = 0;
	}
}