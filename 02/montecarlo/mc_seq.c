#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500000000

void calc_pi(){
    int count = 0;
   double pi = 0;
   for (int i = 0; i < N; i++) {
      double x = (double)rand()/RAND_MAX;
      double y = (double)rand()/RAND_MAX;
      double z = x*x+y*y;
      if (z<=1){
          count++;
      }
   }
   pi=(double)count/N*4;
   printf("# of trials= %d , estimate of pi is %g \n",N,pi);

}

int main(void)
{

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    calc_pi();
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("time: %f seconds\n", cpu_time_used);
}