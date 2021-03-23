// Team: Sonja Dagn, Christoph Wittauer
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define N 500000000
#define NUM_THREAD 1


typedef struct {
    long iterations;
    long count;
} thread_data;

void *calc_pi_thread(void *arg) {
    thread_data *data = (thread_data *) arg;

    unsigned int state = pthread_self();

    long contained = 0;

    for (long i = 0; i < data->iterations; i++) {
        double x = (double) rand_r(&state) / RAND_MAX;
        double y = (double) rand_r(&state) / RAND_MAX;

        if (x*x + y*y < 1)
            contained++;
    }

    data->count = contained;

    pthread_exit(NULL);
}

int main(void) {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    unsigned long split = N / NUM_THREAD;
    
    unsigned long iterations = split * NUM_THREAD;

    thread_data *datas = calloc(NUM_THREAD, sizeof(thread_data));
    for (unsigned int i = 0; i < NUM_THREAD; i++) {
        datas[i].iterations = split;
        datas[i].count = 0;
    }

    pthread_t *thread_ids = calloc(NUM_THREAD, sizeof(pthread_t));

    for (unsigned int i = 0; i < NUM_THREAD; i++) {
        pthread_create(&thread_ids[i], NULL, calc_pi_thread, (void *) &datas[i]);
    }

    // wait for threads
    for (unsigned int i = 0; i < NUM_THREAD; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    // get results of all threads
    unsigned long contained = 0;
    for (unsigned int i = 0; i < NUM_THREAD; i++) {
        contained += datas[i].count;
    }

    double pi = 4 * (double) contained / iterations;

    end = clock();

    free(thread_ids);
    free(datas);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf(
        "Iterations: %ld; threads: %d; pi: %.6lf; time: %.5lf\n",
        iterations, NUM_THREAD, pi, cpu_time_used
    );

    return EXIT_SUCCESS;
}