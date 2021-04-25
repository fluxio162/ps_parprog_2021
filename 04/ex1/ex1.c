#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define ITERATIONS 500000000


int main(void){

    double start, end;

    int x = 0;

    start = omp_get_wtime();


    #pragma omp for schedule(static)
    for(int i = 0; i < ITERATIONS; i++){
        #pragma omp atomic
        x ++;
    }

    end = omp_get_wtime();

    printf("time elapsed: %f seconds, x = %d\n", (end-start), x);

    return EXIT_SUCCESS;
}