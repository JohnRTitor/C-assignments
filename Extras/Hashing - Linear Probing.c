#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100
#define EMPTY -1

void init (int arr[]);

int hash (int key)
{
    return key % MAX_SIZE;
}

int linearProbing (int arr[], int key)
{
    int index = hash(key);
    int attempts = 0;
    while (true)
    {
        if (arr[index] == EMPTY || arr[index] == key)
            return index;
        else
        {
            index = (hash(key) + attempts) % MAX_SIZE;
            attempts++;
            if (attempts == MAX_SIZE)
                return -1;
        }
    }
}

int main ()
{
    int size, arr[MAX_SIZE];
    int data, index;

    init(arr);
    printf("Enter the size: ");
    scanf("%d", &size);

    printf("Enter the elements: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &data);
        int index = linearProbing(arr, data);
        if (index == -1)
            fprintf(stderr, "Hash table is full\n");
        else
            arr[index] = data;
    }

    printf("Enter the element to search: ");
    scanf("%d", &data);
    index = linearProbing(arr, data);
    if (index == -1)
        printf("Element not found\n");
    else
        printf("Element found at index %d\n", index);
}

void init (int arr[])
{
    for (int i; i < MAX_SIZE; i++)
        arr[i] = EMPTY;
}