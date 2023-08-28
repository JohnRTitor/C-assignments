/*
* Name: Two-Way Merge Sort
* Objective:
** Get an array
** Print the array before sorting
** Sort the array using two-way merge sort
** Print the sorted array
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

int readArray (int arr[]);
void printArray (int arr[], int size);
void mergeSortIterative(int arr[], int size);
void merge(int arr[], int low, int mid, int high);


int main ()
{
    int arr[MAX_SIZE];
    int size;

    size = readArray(arr);

    printf("The array before sorting: ");
    printArray(arr, size);

    mergeSortIterative(arr, size);
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
        fprintf(stderr, "Fatal Error: Size out of bounds.\n");
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

/// @brief 2-way merge sort (iterative)
/// @param arr is base address of the array
/// @param size is the size of the array
void mergeSortIterative (int arr[], int size)
{
    int p, i;
    int low, mid, high;

    // number of passes = ceil(log2(size))
    // p represents the size of the subarray to be merged
    for (p = 2; p <= size; p *= 2)
    {
        // subArray size = p
        // for pass 1, subArray size = 2
        // for pass 2, subArray size = 4
        // for pass 3, subArray size = 8...
        // for each pass, two subarrays are merged, then the next two subarrays
        // and so on...
        for (i = 0; i + p - 1 < size; i += p)
        {
            low = i;
            high = i + p - 1;
            mid = (low + high)/2;
            merge(arr, low, mid, high);
        }
    }
    // if the size is not a power of 2, merge the remaining elements
    if (p/2 < size)
        merge(arr, 0, p/2, size - 1);
}

/// @brief merges two sorted subarrays into one sorted array
/// @param arr is the array to be sorted
/// @param low is the lower bound of the array
/// @param mid is the middle of the array
/// @param high is the upper bound of the array
void merge (int arr[], int low, int mid, int high)
{
    int i, j, k;
    int leftSize = mid - low + 1;
    int rightSize = high - mid;
    int left[leftSize], right[rightSize];
    
    // copy the elements to the left and right temporary arrays
    for (i = 0; i < leftSize; i++)
        left[i] = arr[low + i]; // from low to mid

    for (j = 0; j < rightSize; j++)
        right[j] = arr[mid + 1 + j]; // from mid+1 to high
    
    // merge the two arrays back into arr
    i = j = 0;
    for (k = low; i < leftSize && j < rightSize; k++)
        arr[k] = (left[i] <= right[j]) ? left[i++] : right[j++];

    // copy the remaining elements from left, if any
    while (i < leftSize)
        arr[k++] = left[i++];
    // copy the remaining elements from right, if any
    while (j < rightSize)
        arr[k++] = right[j++];
    
}
