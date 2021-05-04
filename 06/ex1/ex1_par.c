#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>


void exclusive_prefix_sum(const int32_t* a, int32_t* outer_b, long length) {
    // initialize b    
    int32_t* b = outer_b + 1;

	int numThreads;
    #pragma omp parallel
    #pragma omp single // must be run by a single thread
    numThreads = omp_get_num_threads();
    // create a tmp array for all values above thread number
	int32_t* tmp_arr =  (int32_t*) calloc((size_t) numThreads, (size_t) sizeof(int32_t));

    
	if(numThreads >= length) {
        for(int i = 1; i <= length; i++) {
            outer_b[i] = outer_b[i - 1] + a[i - 1];
        }
		return;
	}

    // parallize with shared memory b, a, tmp_arr
	# pragma omp parallel shared(b, a, tmp_arr)
    {
		long i;
	    int thread_id = omp_get_thread_num();
        // initialize intervall of each thread
	    long start = thread_id * length / numThreads;
	    long end = (thread_id + 1) * length / numThreads;
		b[start] = a[start];

	    if(thread_id == numThreads - 1) {
	    	end = length;
	    }

	    for(i = start + 1; i < end; i++) {
            b[i] = b[i - 1] + a[i];
        }

        #pragma omp critical
	    tmp_arr[thread_id] = b[end - 1];

        #pragma omp barrier

        int32_t add = 0;
        for(i = 0; i < thread_id; i++){
            add += tmp_arr[i];
        } 

        for(i = start; i < end; i++) {
            b[i] = b[i] + add;
        }
	}
}

void print_array(int32_t* array, long n){

    for(int i = 0; i < n; i++){
        printf("%d, ", array[i]);
    }
    
}

int main(int argc, char* argv[]) {

    if(argc != 2){
		printf("usage: ./ex1_par <n>\n");
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