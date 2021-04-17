#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "omp.h"

// Merge Function
void merge(int32_t arr[], int left, int middle, int right)
{
    int i, j, k;
    int node1 = middle - left + 1;
    int node2 = right - middle;
    int Left[node1], Right[node2];
    for (i = 0; i < node1; i++)
        Left[i] = arr[left + i];
    for (j = 0; j < node2; j++)
        Right[j] = arr[middle + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < node1 && j < node2)
    {
        if (Left[i] <= Right[j])
        {
            arr[k] = Left[i];
            i++;
        }
        else
        {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }
    while (i < node1)
    {
        arr[k] = Left[i];
        i++;
        k++;
    }
    while (j < node2)
    {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

void mergeSort(int32_t arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void printArray(int32_t arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    double start_time = omp_get_wtime();

    unsigned n;
    if (argc == 2)
    {
        n = strtoul(argv[1], NULL, 10);
    }
    else{
        printf("Usage: ./ex3_sq <n>\n");
        return EXIT_FAILURE;
    }

    int32_t arr[n];
    time_t t;
    srand(time(&t));

    for (unsigned i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    printf("The given array is: ");
    printArray(arr, n);
 
    mergeSort(arr, 0, n - 1);
    
    printf("\nThe sorted array is: ");
    printArray(arr, n);


    double end_time = omp_get_wtime();
    double duration  = end_time - start_time;
	printf("\ntime: %2.5f seconds\n",duration);

    return EXIT_SUCCESS;
}