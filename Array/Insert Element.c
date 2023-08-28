#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
// Inserting element to a specified position - max array size can be changed by manipulating the MACRO as needed
int readArray (int arr[]); // Given array base address, reads array and returns size
void printArray(int arr[], int size); // Given array BA, prints array

void insertElement (int arr[], int size, int insertThis, int insertIndex); // needs array BA, size, the element to insert and insertion index

int main()
{
	int arr[MAX_SIZE], size, insertThis, position;
	printf("Enter array\n");
	size = readArray(arr);
	printf("\nWhich element to insert?");
	scanf("%d", &insertThis);
	printf("\nWhere to insert? (Enter positon:)");
	scanf("%d", &position);
	if (position < 1 || position > size+1)
	{
		fprintf(stderr, "Error: The valid range is 1-%d.", size+1);
		exit(-1);
	}
	insertElement(arr, size, insertThis, position-1); // call the function with index (position-1)

	printf("Successfully inserted %d to #%d postion in the array. The modified array is below.\n", insertThis, position);
	printArray(arr, size+1); // size+1 since the element is inserted

	return 0;
}
int readArray (int arr[])
{
	int i, size;
	printf("Enter the size (1-%d):", MAX_SIZE);
	scanf("%d", &size);
	if (size < 1 || size > MAX_SIZE)
	{
		fprintf(stderr, "Invalid size. Valid range (1-%d).", MAX_SIZE);
		exit(-1);
	}
	for (i=0; i<size; i++)
	{
		printf("\tElement#%d:", i+1);
		scanf("%d", &arr[i]);
	}
	return size;
}
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i<size; i++)
	{
		printf("%d, ", arr[i]);
	}
}

void insertElement (int arr[], int size, int insertThis, int insertIndex)
{
	int i;
	for (i=size; i>=insertIndex+1; i--) // shift by one element to the right - start from the end, else it would cause data loss (from size index to insertIndex+1)
	{
		arr[i] = arr[i-1];
	}
	arr[insertIndex] = insertThis;
}