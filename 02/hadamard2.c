// Hadamard 2
#include <stdio.h>
#include<stdlib.h>
#define N 1000

void print_matrix(int c[N][N]){

     
    for (size_t i = 0; i < (unsigned) N; ++i) {
        for (size_t j = 0; j < (unsigned) N; ++j) {   
            printf("%d ", (c[i][j]));
        }
        printf("\n");
    }
}

void calculate_hadamard2(int a[N][N], int b[N][N])
{
   int32_t c[N][N]; 

    for (size_t j = 0; j < N; ++j) { 
        for (size_t i = 0; i < N; ++i) {
        
            c[i][j] = a[i][j]*b[i][j];
        }
    }
}

int main(void){

    int32_t a[N][N];
    int32_t b[N][N];
    
    calculate_hadamard2(a, b);
    
    
    return EXIT_SUCCESS;
}

