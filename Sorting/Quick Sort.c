#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 30
/* QuickSort - uses Hoare's partitioning method and select the median of three (first, middle, last) as pivot. NOTE: pivot gets its proper position after each pass */


int readArray (int arr[]);
void printArray(int arr[], int size);
void swap(int *x, int *y);
void quickSort (int arr[], int lower, int upper);
int medianOfThree (int arr[], int lower, int upper);
int partition (int arr[], int lower, int upper);

int main()
{
	int arr[MAX_SIZE], size;
	size = readArray(arr);
	printf("Before sorting:\n");
	printArray(arr, size);
	printf("\nAfter sorting:\n");
	quickSort (arr, 0, size-1);
	printArray(arr, size);
	return 0;
}

int readArray (int arr[]) // reads array elements and returns size
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

void printArray(int arr[], int size) // prints array
{
	int i;
	for (i=0; i<size; i++)
	{
		printf("%d, ", arr[i]);
	}
}

void swap(int *x, int *y) // swap two integers
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void quickSort (int arr[], int lower, int upper) // sorts an array. TC - best case: O(nlogn), worst case: O(n^2)
{
	int pivotIndex;
	if (lower < upper)
	{
		pivotIndex = partition(arr, lower, upper);
		/* Partition from pivotIndex */
		quickSort (arr, lower, pivotIndex-1);
		quickSort (arr, pivotIndex+1, upper);
	}
}

int partition (int arr[], int lower, int upper) // partitions from a position where every smaller element is at left side and larger in right side
{
	int p, q, pivot;
	
	pivot = medianOfThree(arr, lower, upper); // selects the pivot from first, middle and last elements and moves it to first(lower index)
	p = lower; // p sits on pivot location, and moves to right (increments)
	q = upper+1; // q sits on the upper+1 location, and moves to left (decrements)
	while (p<=q) // until q crosses p
	{
		while (arr[++p] < pivot); // increment p until an element is greater than pivot encountered and this condition becomes false
		while (arr[--q] > pivot); // decrement q until an element is less than pivot encountered
		if (p < q) // q still hasn't crossed p
		{
			swap(&arr[p], &arr[q]); // swap p'th and q'th element
		}	
	}
	swap(&arr[lower], &arr[q]); // pivot gets its proper position
	return q; // return pivot's current position
}

int medianOfThree(int arr[], int lower, int upper) // calculates the median and swaps it with the first element
{
    int pivotIndex, mid = (lower + upper)/2;
    /* Select the pivot element, which would be median of three/exclusively greater than rest of the two */
    if ((arr[lower] > arr[mid]) ^ (arr[lower] > arr[upper])) 
        pivotIndex = lower;
    else if ((arr[mid] < arr[lower]) ^ (arr[mid] < arr[upper])) 
        pivotIndex = mid;
    else
    	pivotIndex = upper;
    
    // move it to the beginning of the array, if needed
    if (pivotIndex != lower)
    	swap(&arr[pivotIndex], &arr[lower]);
    return arr[lower]; // return the pivot element
}