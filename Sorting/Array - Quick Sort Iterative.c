/*
* Objective:
** Get an array of integers from the user
** Sort the array using quick sort
*** Use the partition function
*** For each partition, save the upper and lower bound of the subarrays
*** Push the bounds into the stack
*** Pop the bounds from the stack and repeat the process
** Print the sorted array
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

int readArray (int arr[]);
void printArray (int arr[], int size);
void swap (int *a, int *b);
int partition (int arr[], int lower, int upper);
void quickSortIterative (int arr[], int size);


int main ()
{
    int arr[MAX_SIZE];
    int size;

    size = readArray(arr);
    printf("The array before sorting: ");
    printArray(arr, size);
    quickSortIterative(arr, size);
    printf("The array after sorting: ");
    printArray(arr, size);
    return 0;
}
/// @brief reads an array and its size from the user
/// @param arr is the array to be read
/// @return the size of the array
int readArray (int arr[])
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    if (size < 1 ||size > MAX_SIZE)
    {
        fprintf(stderr, "Error: Size out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    return size;
}

/// @brief prints the array seperated by a space
/// @param arr is the array to be printed
/// @param size size of the array
void printArray (int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/// @brief swaps two integers
/// @param a is the first integer, passed by reference
/// @param b is the second integer, passed by reference
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/// @brief partitions the array into two subarrays
/// @param arr is the array to be partitioned
/// @param lower is the lowermost index of the sub-array
/// @param upper is the uppermost index of the sub-array
/// @return returns the index of the pivot element
int partition (int arr[], int lower, int upper)
{
    int pivot = arr[lower];
    int i = lower + 1;
    int j = upper;

    while (i < j)
    {
        // i starts from left and goes to right
        // stops when it encounters an element greater than pivot
        while (arr[i] < pivot)
            i++;
        // j starts from right and goes to left
        // stops when it encounters an element smaller than pivot
        while (arr[j] > pivot)
            j--;
        if (i < j)
            swap(&arr[i], &arr[j]);
    }
    swap(&arr[lower], &arr[j]);
    return j;
}

/// @brief sorts the array using quick sort
/// @param arr is the array to be sorted
/// @param size is the size of the array
void quickSortIterative (int arr[], int size)
{
    int lower, upper;
    int stack[MAX_SIZE * 2];
    int top = -1;
    int pivotIndex;

    // push the initial values of lower and upper into the stack
    stack[++top] = lower = 0;
    stack[++top] = upper = size - 1;

    while (top != -1) // until stack becomes empty
    {
        // pop upper and lower
        upper = stack[top--];
        lower = stack[top--];

        // set pivot element at its correct position in sorted array and partition from pivot
        pivotIndex = partition(arr, lower, upper);

        if (pivotIndex - 1 > lower) // if there are elements on the left side of pivot
        {
            // push the lower and upper bounds of the left subarray into the stack
            stack[++top] = lower;
            stack[++top] = pivotIndex - 1;
        }

        if (pivotIndex + 1 < upper) // if there are elements on the right side of pivot
        {
            // push the lower and upper bounds of the right subarray into the stack
            stack[++top] = pivotIndex + 1;
            stack[++top] = upper;
        }
    }
}
