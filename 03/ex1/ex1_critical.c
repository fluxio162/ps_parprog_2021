// Team: Sonja Dagn, Christoph Wittauer
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 50000000

int main(void) {

    unsigned int circle_points = 0;
    unsigned int iterations = 0;

    double start = omp_get_wtime();


    #pragma omp parallel
    {
        unsigned int seed = time(NULL);
        unsigned int local_circle_points = 0;

        int num_threads = omp_get_num_threads();

        unsigned int chunk_size = N / num_threads;

        for (unsigned int i = 0; i < chunk_size; i++) {
            double x = (double) rand_r(&seed) / RAND_MAX;
            double y = (double) rand_r(&seed) / RAND_MAX;

            if (x*x + y*y < 1)
                local_circle_points++;
            }

        //When this the omp critical pragma is used
        //, a thread waits at the beginning of a critical section 
        //until no other thread in the team is executing a critical section having the same name.
        #pragma omp critical
        {
            circle_points += local_circle_points;
            iterations += chunk_size;
        }
        
    }

    double pi = 4 * (double) circle_points / iterations;

    double end = omp_get_wtime();

    printf("Iterations: %d; pi: %.6lf; time: %.5lf seconds\n", iterations, pi, (end - start));

    return EXIT_SUCCESS;
}