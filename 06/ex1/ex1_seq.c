#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>

void exclusive_prefix_sum(const int32_t* a, int32_t* b, long n) {
    for (int i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i - 1];
    }
}

void print_array(int32_t* array, long n){

    for(int i = 0; i < n; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");
    
}

int main(int argc, char* argv[]) {

    if(argc != 2){
		printf("usage: ./ex1_seq <n>\n");
		exit(EXIT_FAILURE);
	}

	long n = strtol((const char*) argv[1], NULL, 10);
    int32_t* a = (int32_t*)calloc((size_t) n, (size_t) sizeof(int32_t));
    int32_t* b = (int32_t*)calloc((size_t) n, (size_t) sizeof(int32_t));

	for(int i = 0; i < n; i++){
        a[i] = 1;
    }


    double start = omp_get_wtime();
    exclusive_prefix_sum(a, b, n);
    double end = omp_get_wtime();

    // Get last element
	printf("Elapsed time: %.5f seconds\nlast b = %d\n", end - start, b[n-1]);

	free(a);
	free(b);
	return EXIT_FAILURE;
}