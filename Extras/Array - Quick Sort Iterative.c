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

struct tuple
{
    int left;
    int right;
};

int main ()
{
    return 0;
}

int readArray (int arr[])
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    if (size < 1 ||size > MAX_SIZE)
    {
        fprintf(stderr, "Error: Size out of bounds.");
        exit(EXIT_FAILURE);
    }
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    return size;
}

void printArray (int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

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