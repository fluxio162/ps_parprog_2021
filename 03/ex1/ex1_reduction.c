// Team: Sonja Dagn, Christoph Wittauer
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 500000000

int main(void) {

    unsigned int circle_points = 0;
    unsigned int iterations = 0;

    double start = omp_get_wtime();

    #pragma omp parallel reduction(+: circle_points, iterations)
    {
        unsigned int seed = time(NULL);

        int num_threads = omp_get_num_threads();

        iterations = (N / num_threads);

        for (unsigned long i = 0; i < iterations; i++) {
            double x = (double) rand_r(&seed) / RAND_MAX;
            double y = (double) rand_r(&seed) / RAND_MAX;

            if (x*x + y*y < 1)
                circle_points++;
        }
    }

    double pi = 4 * (double) circle_points / iterations;

    double end = omp_get_wtime();

    printf("Iterations: %d; pi: %.6lf; time: %.5lf\n", iterations, pi, (end-start));

    return EXIT_SUCCESS;
}