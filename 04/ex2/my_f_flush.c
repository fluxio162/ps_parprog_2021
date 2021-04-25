#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {
   int data, flag = 0;

   // parallize this code section with two threads
   #pragma omp parallel num_threads(2)
   {

      /*
         First flush ensures flag is written after data
         Second flush ensures flag is witten to memory
      */
      if (omp_get_thread_num()==0) {
         sleep(2);
         /* Write to the data buffer that will be read by thread */
         data = 42;
         #pragma omp flush
         /* Set flag to release thread 1 */
         flag = 1;
         #pragma omp flush
      }
      else if (omp_get_thread_num()==1) {
         /* Loop until we see the update to the flag */

         /*
            First and second flushes ensure flag is read from memory
            Third flush ensures corect ordering of flushes
         
         */
         #pragma omp flush
         while (flag < 1) {
            #pragma omp flush
         }
         #pragma omp flush
         /* print flag and data */
         printf("flag=%d data=%d\n", flag, data);
      }
      // 2 threads are created
      // first thread writes in data and sets flag to 1 to unlock the second thread
      // second thread waits until flag is bigger than zero then flag and data are printed
      // The omp flush directive identifies a point at which the compiler ensures that all threads
      // in a parallel region have the same view of specified objects in memory.

      /*
      • This is incorrect code
      • The compiler and/or hardware may re-order the reads/writes
      to a and flag, or flag may be held in a register.
      */

     
   }

   return 0;
}
