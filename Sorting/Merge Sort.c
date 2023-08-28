#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 30
/* Merge Sort, uses divide and conquer */


int readArray (int arr[]);
void printArray(int arr[], int size);
void mergeSort (int arr[], int lower, int upper);
void merge (int arr[], int lower, int mid, int upper);

int main()
{
	int arr[MAX_SIZE], size;
	size = readArray(arr);
	printf("Before sorting:\n");
	printArray(arr, size);
	printf("\nAfter sorting:\n");
	mergeSort (arr, 0, size-1);
	printArray(arr, size);
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
void mergeSort (int arr[], int lower, int upper)
{
	int mid = (lower + upper)/2;
	if (lower < upper)
	{
		// divide into subproblems
		mergeSort(arr, lower,mid);
		mergeSort(arr, mid+1, upper);
		// Combine the solutions
		merge(arr, lower, mid, upper);
	}
}
void merge(int arr[], int lower, int mid, int upper)
{
	int i, j, k, leftSize, rightSize;

	leftSize = mid - lower + 1;
	rightSize = upper - mid;
	int left[leftSize], right[rightSize];

	/* Clone the elements to temporary arrays */
	for (i = 0; i < leftSize; i++)
		left[i] = arr[lower + i];
	
	for (j = 0; j < rightSize; j++)
		right[j] = arr[mid + 1 + j];

	// Merge the temporary arrays, back into arr[lower...upper], sort them one by one
	for (i = 0, j = 0, k = lower; i < leftSize && j < rightSize; k++)
	{
		// if left array's element is smaller than right's, copy it to arr
		// else copy the right array's element to arr
		arr[k] = (left[i] <= right[j]) ? left[i++] : right[j++];
	}
	// Copy the remaining elements of left array, if any
	while (i < leftSize)
		arr[k++] = left[i++];
	// Copy the remaining elements of right subarray, if any
	while (j < rightSize)
		arr[k++] = right[j++];
}