/*
* Objective:
** get an integer array (arr) from user
** copy it in another array (sortedArr)
** sort the new array (sortedArr) in descending order
** copy the original array (arr) again
** replace the new array (positions) elements with the postions of the elements in sorted array
** print the positions array
*/
#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 50

int readArray (int arr[]);
void printArray (int arr[], int size);
void copyArray (int source[], int destination[], int size);
void bubbleSortDescending (int arr[], int size);
void getSortedPositions(int arr[], int positions[], int size);
void swap(int *a, int *b);

int main ()
{
    int arr[MAX_SIZE], positions[MAX_SIZE];
    int size;

    while ((size = readArray(arr)) == -1); // read the array until the size is valid
    
    printf("You entered: ");
    printArray(arr, size);

    getSortedPositions(arr, positions, size);
    printf("Here is the sorted positions of the elements: ");
    printArray(positions, size);

    return 0;
}

/// @brief gets the size from the user and the elements of the array
/// @param arr 
/// @return returns the size of the array, -1 if the size is invalid
int readArray (int arr[])
{
    int i, size;

    printf("Enter the size of the array: ");
    scanf("%d", &size);
    if (size > MAX_SIZE || size < 1)
    {
        fprintf(stderr, "Error: size should be less than or equal to %d.\n", MAX_SIZE);
        return -1;
    }

    printf("Enter the elements of the array: ");
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);
    return size;
}

/// @brief prints an array elements with comma and space
/// @param arr 
/// @param size 
void printArray (int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf("\n");
}

/// @brief copies source array to destination array
/// @param source 
/// @param destination 
/// @param size 
void copyArray (int source[], int destination[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        destination[i] = source[i];
}



/// @brief sorts an array in descending order
/// @param arr base address of the array
/// @param size 
void bubbleSortDescending (int arr[], int size)
{
    int i, j;
    int swapped;

    for (i = 0; i < size - 1; i++)
    {
        swapped = false;
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

/// @brief swaps two integers
/// @param a first integer called by reference
/// @param b second integer called by reference
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/// @brief search for an element in an array
/// @param arr 
/// @param size 
/// @param searchFor 
/// @return the index of the element if found, -1 otherwise
int searchElement (int arr[], int size, int searchFor)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (arr[i] == searchFor)
            return i;
    }
    return -1;
}

/// @brief copies the sorted positions of the elements
/// @param arr base address of the array
/// @param positions base address of the positions array
/// @param size size of the array
void getSortedPositions (int arr[], int positions[], int size)
{
    int i, j;
    int sortedArr[MAX_SIZE];

    copyArray(arr, sortedArr, size);
    bubbleSortDescending(sortedArr, size);
    for (i = 0; i < size; i++)
    {
        j = searchElement(sortedArr, size, arr[i]);
        positions[i] = j + 1; // +1 because the index starts from 0
    }
}