#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROW 10
#define MAX_COLM 10

typedef struct matrix
{
	int data[MAX_ROW][MAX_COLM];
	int row;
	int colm;
} MATRIX;
void readMatrix(MATRIX *);
void printMatrix(MATRIX);
int multiplyMatrix(MATRIX, MATRIX, MATRIX *);

int main()
{
	MATRIX A, B, multiply;
	int status;
	printf("Enter matrix A:\n");
	readMatrix(&A);
	printf("Enter matrix B:\n");
	readMatrix(&B);
	status = multiplyMatrix(A, B, &multiply); // multiply A and B and store it in multiply matrix, also catch the returned value in status
	if (status == true) // multiplication is successful
	{
		printf("\nMatrix A: \n");
		printMatrix(A);
		printf("\nMatrix B: \n");
		printMatrix(B);
		printf("\nMultiplication is successful. The result is below.\n");
		printMatrix(multiply);
	}
	else // multiplication is unsuccessful
	{
		fprintf(stderr, "Multiplication is unsuccessful. Matrix A's column count(%d) should be equal to Matrix B's row count(%d).", A.colm, B.row);
	}
	return 0;
}

void readMatrix(MATRIX *M)
{
	int i, j;
	printf("\n\tEnter the no of rows:");
	scanf("%d", &M->row);
	printf("\n\tEnter the no of columns:");
	scanf("%d", &M->colm);
	if ((M->row) < 1 || (M->row) > MAX_ROW || (M->colm) < 1 || (M->colm) > MAX_COLM)
	{
		fprintf(stderr, "\nError: Row count's valid range 1-%d. Column count's valid range 1-%d.", MAX_ROW, MAX_COLM);
		exit(-1);
	}
	for (i = 0; i < (M->row); i++)
	{
		for (j = 0; j < (M->colm); j++)
		{
			printf("\tElement#%d-%d:", i + 1, j + 1);
			if (scanf("%d", &(M->data)[i][j]) != 1)
			{
				fprintf(stderr, "Invalid value entered.");
				exit(-1);
			}
		}
	}
}
void printMatrix(MATRIX M)
{
	int i, j;
	for (i = 0; i < M.row; i++)
	{
		for (j = 0; j < M.colm; j++)
		{
			printf("%d\t", M.data[i][j]);
		}
		printf("\n");
	}
}

int multiplyMatrix(MATRIX A, MATRIX B, MATRIX *multiply) // returns true if successful else returns false
{
	int i, j, k;
	if (A.colm != B.row) // multiplication is not possible
	{
		return false;
	}
	
	multiply->row = A.row; // A matrix's row count becomes the row count of resultant
	multiply->colm = B.colm; // B matrix's column count becomes the column count of resultant
	
	for (i=0; i<(multiply->row); i++)
	{
		for (j=0; j<(multiply->colm); j++)
		{
			(multiply->data)[i][j] = 0; // initialize multiply matrix's (i, j) element to 0
			for (k=0; k<A.colm; k++)
			{
				(multiply->data)[i][j] = A.data[i][k] * B.data[k][j]; // By dot product of corresponding row of A and corresponding column of B
			}
		}
	}
	return true;
}