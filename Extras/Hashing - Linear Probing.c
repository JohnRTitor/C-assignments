#include <stdio.h>
#define MAX_SIZE 100
#define EMPTY -1

int hash (int key, int size)
{
    return key % size;
}

int linearProbing (int arr[], int key, int size)
{
    while ()
        if (arr[hash(key, size)] == EMPTY)
            return hash()
}

int main ()
{
    int size, arr[MAX_SIZE];

    init(arr);
    printf("Enter the size:");
    scanf("%d", &size);

    printf("Enter the elements:");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void init (int arr[])
{
    for (int i; i < MAX_SIZE; i++)
        arr[i] = EMPTY;
}