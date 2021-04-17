// Team: Sonja Dagn, Christoph Wittauer
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <pthread.h>
#define THREAD_NUM 1
#define N 500000000

typedef struct {
    long iterations;
    long circle_points;
} thread_data;

void *monte_carlo_pi_thread(void *arg)
{
    thread_data *t_data = (thread_data *) arg;
    
    unsigned int state = pthread_self();

    long circle_points = 0;

    for(int i = 0; i < t_data->iterations; i++){
        double x = (double) rand_r(&state) / RAND_MAX;
        double y = (double) rand_r(&state) / RAND_MAX;
        if ((x*x + y*y) <= 1){
            circle_points++;
        }
    }

    t_data->circle_points = circle_points;

    pthread_exit(NULL);
}

void monte_carlo_pi_seq(){
    // Simply generate x and y so if x2 + y2 <= 1 increment number of points
    double circle_points = 0;
    double square_points = 0;
    double pi = 0;
    
    for(int i = 0; i < N; i++){
        double x = (double)(rand() % (N + 1)) / N;
        double y = (double)(rand() % (N + 1)) / N;
        if ((x*x + y*y) <= 1){
            circle_points++;
        }
        square_points++;
    }

    pi = 4 * (circle_points/square_points);
    printf("pi: %f\n",pi);
}

int main(void){

    // calculate iterations for each threads
    int thread_iteations = N/THREAD_NUM;

    // allocate thread_data
    thread_data *t_data = calloc(THREAD_NUM, sizeof(thread_data));

    // fill all thread data
    for(int i = 0; i < THREAD_NUM; i++){
        t_data[i].iterations = thread_iteations;
        t_data[i].circle_points = 0;
    }

    pthread_t *thread_ids = calloc(THREAD_NUM, sizeof(pthread_t));

    // create N threads
    for(unsigned int i = 0; i < THREAD_NUM; i++){
        pthread_create(&thread_ids[i], NULL, monte_carlo_pi_thread, (void *) &t_data[i]);
    }


    // wait for all threads
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_join(thread_ids[i], NULL);
    }

    // get result
    double circle_points = 0;

    for(int i = 0; i < THREAD_NUM; i++){
        circle_points += t_data[i].circle_points;
    }

    double pi = 4 * (double) (circle_points/N);

    printf("%f\n", pi);

    //monte_carlo_pi_seq();

    free(t_data);
    free(thread_ids);
    
    exit(0);
}