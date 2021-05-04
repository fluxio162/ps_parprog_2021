#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
 
int N =  0;
int count = 0;

int isSafe(char mat[][N], int r, int c)
{
    // return 0 if two queens share the same column
    for (int i = 0; i < r; i++)
    {
        if (mat[i][c] == 'Q') {
            return 0;
        }
    }
 
    // return 0 if two queens share the same diagonal
    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--)
    {
        if (mat[i][j] == 'Q') {
            return 0;
        }
    }
 
    // return 0 if two queens share the same diagonal
    for (int i = r, j = c; i >= 0 && j < N; i--, j++)
    {
        if (mat[i][j] == 'Q') {
            return 0;
        }
    }
 
    return 1;
}
 
void nQueen(char mat[][N], int r)
{
    if (r == N)
    {
        count = count + 1;
        return;
    }
 
    // place queen at every square in the current row `r`
    // and recur for each valid movement
    for (int i = 0; i < N; i++)
    {
        if (isSafe(mat, r, i))
        {
            mat[r][i] = 'Q';
 
            nQueen(mat, r + 1);
 
            mat[r][i] = '-';
        }
    }
}
 
int main(int argc, char *argv[])
{   
    if (argc == 2){
        N = strtoul(argv[1], NULL, 10);
    }
    else{
        printf("Usage: ./ex2_seq <N>\n");
        return EXIT_FAILURE;
    }
    char mat[N][N];

    memset(mat, '-', sizeof mat);

    double startTime = omp_get_wtime();

    nQueen(mat, 0);
    
    double endTime = omp_get_wtime();
    double realTime = endTime - startTime;

    printf("time: %.5f, result: %d\n",realTime, count);
 
    return 0;
}