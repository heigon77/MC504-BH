#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THR 10

void* f_thread(void *v) {
  int* id = (int *) v;
  printf("Thread %d\n", id[0]);
  printf("Thread %d\n", id[1]);
  return NULL; 
} 


int main(int argc, char const *argv[])
{

    int *nums = (int*)malloc((2)*sizeof(int));

    nums[0] = 10;
    nums[1] = 20;

    pthread_t thr;


    pthread_create(&thr, NULL, f_thread, (void*) nums);

    pthread_join(thr, NULL); 

    return 0;
}
