#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ROW 10
#define MAX_COLM 10

// Trace and norms of a matrix
typedef struct matrix
{
	int data[MAX_ROW][MAX_COLM];
	int row;
	int colm;
} MATRIX;
void readMatrix(MATRIX *);
void printMatrix(MATRIX);
int getTrace(MATRIX);
double getNormal(MATRIX);

int main()
{
	MATRIX A;
	printf("Enter matrix A:\n");
	readMatrix(&A);
	printf("Matrix A:\n");
	printMatrix(A);
	printf("Trace is %d. Normal is %.3lf.", getTrace(A), getNormal(A));
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

// Trace is the sum of elements in the main diagonal
int getTrace (MATRIX M)
{
	int i, j, trace=0;
	for (i = 0; i < M.row; i++)
	{
		for (j = 0; j < M.colm; j++)
		{
			if (i == j)
			{
				trace += M.data[i][j];
			}
		}
	}
	return trace;
}
// Normal is the square root of sum of all elements
double getNormal(MATRIX M)
{
	int i, j, sum=0;
	for (i = 0; i < M.row; i++)
	{
		for (j = 0; j < M.colm; j++)
		{
			sum += M.data[i][j];
		}
	}
	return sqrt(sum);
}