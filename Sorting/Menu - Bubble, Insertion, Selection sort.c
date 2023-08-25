#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 50
/* Menu to perform Bubble, Selection and Insertion sort */
int readArray (int *);
void printArray(int *, int);
void clearBuffer (void);
void swap(int *, int *);
void bubbleSort (int *, int);
void selectionSort (int *, int);
void insertionSort(int *, int);
int main()
{
	int option, size, arr[MAX_SIZE];
	printf("Enter array:");
	while ((size = readArray(arr)) == -1); // read array and validate the size, for invalid input, the loop is initiated again
	while (true)
	{
		printf("\nEnter an option: \n\tPress '1' for Bubble sort. \n\tPress '2' for Selection sort. \n\tPress '3' for Insertion sort. \n\tPress '4' to re-enter the array. \n\tPress '5' to exit.");
		scanf("%d", &option);
		
		if (option == 5)
		{
			printf("Program exited.");
			exit(1);
		}
		clearBuffer();
		
		switch (option)
		{
		case 1:
			bubbleSort(arr, size);
			printf("Successfully sorted the array using Bubble sort.\n");
			printArray(arr, size);
			break;
		case 2:
			selectionSort(arr, size);
			printf("Successfully sorted the array using Selection sort.\n");
			printArray(arr, size);
			break;
		case 3:
			insertionSort(arr, size);
			printf("Successfully sorted the array using Insertion sort.\n");
			printArray(arr, size);
			break;
		case 4:
			printf("\nPlease re-enter the array.");
			while ((size = readArray(arr)) == -1); // read array and validate the size
			break;
		default: printf("Invalid input. Please try again.");
		}
	}
	return 0;
}

/* returns size when array reading is successful, else returns -1 */
int readArray(int arr[])
{
	int i, size;
	printf("\n\tEnter the size:");
	scanf("%d", &size);
	clearBuffer();
	if (size < 1 || size > MAX_SIZE)
	{
		fprintf(stderr, "Invalid size entered. Please try again.");
		return -1;
	}
	for (i = 0; i < size; i++)
	{
		printf("\tElement#%d:", i + 1);
		if (scanf("%d", &arr[i]) != 1)
		{
			fprintf(stderr, "Invalid input. Please try again.");
			clearBuffer();
			i--; // reinitiates the iteration again
		}
	}
	return size;
}

/* Prints array with comma in between */
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d, ", arr[i]);
	}
}

/* Bubble sort function - modified for best case O(n) */
void bubbleSort(int arr[], int size)
{
	int i, j, swapped;
	for (i = 0; i < size - 1; i++)
	{
		swapped = false;
		for (j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1]) // compare and start swapping so largest element ends up in the last position, then before that second largest, ... 
			{
				swap(&arr[j], &arr[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false) // if not swapped, array is already sorted, so break
		{
			break;
		}
	}
}
/* Selection sort function */
void selectionSort(int arr[], int size)
{
	int i, j, minIndex;
	for (i = 0; i < size - 1; i++)
	{
		minIndex = i;
		for (j = i + 1; j < size; j++) //find the minimum element from the unsorted portion
		{
			if (arr[minIndex] > arr[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i) // if i'th element is not the minimum element, then swap 
		{
			swap(&arr[minIndex], &arr[i]);
		}
	}
}
/* Insertion sort function - modified for best case O(n) */
void insertionSort(int arr[], int size)
{
	int i, j, key;
	for (i = 1; i < size; i++)
	{
		key = arr[i];
		j = i - 1; // set the initial position for comparison
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j]; // shift elements to the right by one position
			j--;
		}

		if (j+1 != i) // after shifting, insert key to it's correct position if it is not already at its correct position
		{
			arr[j + 1] = key;
		}
	}
}
/* Swap two integers */
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
/* Clear input buffer */
void clearBuffer()
{
	char ch;
	while ((ch = getchar()) != '\n' && (int)ch != EOF); // discard leftover characters in input buffer until \n or EOF is reached
}