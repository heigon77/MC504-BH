#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THR 10

void* f_thread(void *v) {
  int id = (int) v;
  printf("Thread %d\n", id);  
  return NULL; 
} 


int main(int argc, char const *argv[])
{

    pthread_t thr[N_THR];
    int i;

    for (i = 0; i < N_THR; i++) 
        pthread_create(&thr[i], NULL, f_thread, (void*) i);

    for (i = 0; i < N_THR; i++) 
        pthread_join(thr[i], NULL); 

    return 0;
}
