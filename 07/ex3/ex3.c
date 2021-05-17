#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<xmmintrin.h>

void print_array(float* array, long n){
    printf("[");
    for(int i = 0; i < n; i++){
        printf(" %f ", array[i]);
    }
    printf("]\n");
    
}

void vector_multiplication(__m128 a, __m128 b, __m128 c, int size, int repetitions){
    #pragma omp simd
    for(int run = 0; run < repetitions; ++run) {
        for(int i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
		printf("usage: ./ex1_seq <size> <repetitions>\n");
		exit(EXIT_FAILURE);
	}

	long size = strtol((const char*) argv[1], NULL, 10);
    long repetitions = strtol((const char*) argv[2], NULL, 10);

    // initialize constant vectors
    float a[size];
    float b[size];
    float c[size];

    __m128 _a =  _mm_load_ps((float *) a);
    __m128 _b =  _mm_load_ps((float *) b);
    __m128 _c =  _mm_load_ps((float *) c);

    for(int i=0;i<size;i++){
        _a[i]=1; 
        _b[i]=1; 
        _c[i]=1; 
    }

    
  
    double start = omp_get_wtime();
    vector_multiplication(_a,_b,_c,size, repetitions);
    double end = omp_get_wtime();

    printf("Elapsed time: %.5f seconds for %ld repetitions and %ld vector size.\n", end - start, repetitions, size);
    
    return EXIT_SUCCESS;
}