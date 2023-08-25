#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
// Merging - array max size can be manipulated by the above macro
int readArray (int arr[]); // Given array base address, reads array size and array elements, returns the size
void printArray(int arr[], int size); // Given array BA, prints array elements with , in between
int mergeArray(int arr[], int arrSize, int brr[], int brrSize, int mergedArr[]); // appends brr to arr and stores in a seperate array, returns the total size

int main()
{
	int arr[MAX_SIZE], brr[MAX_SIZE], mergedArr[2*MAX_SIZE], arrSize, brrSize, mergedSize;
	printf("Enter array#1\n");
	arrSize = readArray(arr);
	printf("Enter array#2\n");
	brrSize = readArray(brr);
	mergedSize = mergeArray(arr, arrSize, brr, brrSize, mergedArr);
	printf("Arrays successfully merged. Total size after merge is %d. Merged array shown below:", mergedSize);
	printArray(mergedArr, mergedSize);
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
int mergeArray(int arr[], int arrSize, int brr[], int brrSize, int mergedArr[])
{
	int i, j, k, mergedSize = arrSize+brrSize;
	for (i=0, j=0, k=0; k<mergedSize; k++)
	{
		mergedArr[k] = (k<arrSize) ? arr[i++] : brr[j++]; // i is for arr, j is for brr, and k loop counter is for mergedArray
	}
	return mergedSize;
}