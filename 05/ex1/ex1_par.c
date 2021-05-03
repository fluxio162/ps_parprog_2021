# include <stdio.h>
# include <stdlib.h>
# include <omp.h>

// Parallel implementation

int delannoy_number(int n,int m){

    if (m == 0||n == 0){
        return 1;
    }
    return delannoy_number(m-1, n) + delannoy_number(m-1,n-1) + delannoy_number(m,n-1);
}

int main (void){
    int n = 3;
    int m = 3;

    printf("%d\n", delannoy_number(n,m));
    return EXIT_SUCCESS;
}