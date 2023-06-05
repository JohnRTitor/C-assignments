#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
// Binary search
int readArray (int arr[]); // Gen array base address, reads array and returns size
int binarySearch(int arr[], int lowerBound, int upperBound, int searchFor); // Given array BA, lower array bound, upper bound and element to look for, returns the index where it is first found

int compare (const void *x, const void *y) // compare function for quick sort
{
	return (*(int *)x - *(int *)y);
}

int main()
{
	int i, arr[MAX_SIZE], size, searchFor, result;
	size = readArray(arr);
	printf("Sorted array is:");
	qsort(arr, size, sizeof(arr[0]), compare); // first sort the array
	
	for (i = 0; i < size; i++)
		printf("%d, ", arr[i]);
	printf("Which element to find?");
	scanf("%d", &searchFor);
	result = binarySearch(arr, 0, size-1, searchFor); // initially for full array bound is 0 to size-1
	if (result != -1)
	{
		printf("%d found in array in position #%d.", searchFor, result+1);
	}
	else
	{
		printf("%d not found in the array.", searchFor);
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

int binarySearch(int arr[], int lowerBound, int upperBound, int searchFor)
{
	int mid = (lowerBound + upperBound)/2;
	if (lowerBound <= upperBound)
	{
		if (arr[mid] == searchFor) // if the middle element is the one we are looking for
		{
			return mid;
		}
		else if (arr[mid] < searchFor) // then the element must be in the right side
		{
			return binarySearch(arr, mid+1, upperBound, searchFor);
		}
		else // then the element must be in the left side
		{
			return binarySearch(arr, lowerBound, mid-1, searchFor);
		}
	}
	else
	{
		return -1; // if the element is not present in the array
	}
}