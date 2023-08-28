#include <stdio.h>
#define MAX_SIZE 100

// Function to swap two numbers
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

// Function to perform heapify operation, max heap
void heapify(int arr[], int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	if (largest != i)
	{
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

// Function to perform heap sort
void heapSort(int arr[], int n)
{
	int i;
	// Build heap (rearrange array)
	for (i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Extract elements from heap one by one
	for (i = n - 1; i > 0; i--)
	{
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}

// Function to print an array
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// Test the program
int main()
{
	int arr[MAX_SIZE];
	int i, n;
	printf("How many elements?");
	scanf("%d", &n);
	if (n < 1 || n > MAX_SIZE)
	{
		fprintf(stderr, "Error: Invalid size entered.");
		return 1;
	}
	printf("Enter the elements seperated by a space: ");
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	printf("Original array: ");
	printArray(arr, n);

	heapSort(arr, n);

	printf("Sorted array: ");
	printArray(arr, n);

	return 0;
}
