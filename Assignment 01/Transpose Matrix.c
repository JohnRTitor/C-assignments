#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10
#define MAX_COLM 10

// transpose a matrix

typedef struct matrix
{
	int data[MAX_ROW][MAX_COLM];
	int row;
	int colm;
} MATRIX;
void readMatrix(MATRIX *);
void printMatrix(MATRIX);
void transposeMatrix(MATRIX, MATRIX *);

int main()
{
	MATRIX A, A_Trans;
	
	printf("Enter matrix A:\n");
	readMatrix(&A);
	
	printf("\nA matrix:\n");
	printMatrix(A);
	transposeMatrix(A, &A_Trans);
	printf("\nsuccessfully transposed. A_transpose is:\n");
	printMatrix(A_Trans);

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

void transposeMatrix(MATRIX M, MATRIX *M_Trans)
{
	int i, j;
	M_Trans->row = M.colm;
	M_Trans->colm = M.row;

	for (i = 0; i < (M_Trans->row); i++)
	{
		for (j = 0; j < (M_Trans->colm); j++)
		{
			(M_Trans->data)[i][j] = M.data[j][i]; // M's row becomes the column of M_trans and vice versa
		}
	}
}