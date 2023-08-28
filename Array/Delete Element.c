#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
// Delete all occurances of a particular element from an array
int readArray (int arr[]); // Given array base address, reads array and returns size
void printArray(int arr[], int size); // Given array BA and size, prints array

int deleteElement (int arr[], int size, int target); // Given arr BA, size, the target element, removes it and returns how many times it got deleted

int main()
{
	int arr[MAX_SIZE], size, target, count;
	printf("Enter array\n");
	size = readArray(arr);
	printf("\nWhich element to delete?");
	scanf("%d", &target);
	count = deleteElement(arr, size, target);
	if (count != 0)
	{
		printf("%d found %d times in the array and successfully deleted. The modified array is given below:\n", target, count);
		printArray(arr, size-count);
	}
	else
	{
		printf("%d not found in the array. The original array is given below:\n", target);
		printArray(arr, size);
	}

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

int deleteElement (int arr[], int size, int target)
{
	int i, j, count = 0;
	for (i=0; i<size; i++)
	{
		if (arr[i] == target)
		{
			for (j=i; j<size-1; j++)
			{
				arr[j] = arr[j+1]; // shifts element to left to delete
			}
			count++;
		}
	}
	return count;
}