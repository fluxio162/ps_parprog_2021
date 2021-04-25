#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

/*
OpenMP implementation example
Details of implementation/tutorial can be found here: http://madhugnadig.com/articles/parallel-processing/2017/02/25/parallel-computing-in-c-using-openMP.html
*/

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);
void printArray(int32_t arr[], int n);


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

    time_t t;
    srand(time(&t));

   int* arr = (int *)malloc(sizeof(int) * n);
    for (unsigned i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    printf("Unsorted array:\n");
    printArray(arr, n);
    mergesort(arr, 0, n-1);
    printf("\nSorted array :\n");
    printArray(arr, n);

    double end_time = omp_get_wtime();
    double duration  = end_time - start_time;
	printf("\ntime: %2.5f seconds\n",duration);
        
    return 0;
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
 
void mergesort(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
    
                mergesort(a,i,mid);        //left recursion
           

     
                mergesort(a,mid+1,j);    //right recursion
    

        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;

    
    
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}