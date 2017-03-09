#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THREADS 4

pthread_t tid[N_THREADS]; // container for 4 threads

void *handleThread(void *arg) {
  pthread_t id = pthread_self();
  int i = 0;
  int number = *(int*)arg;

  // every thread does the same, so just print a number 100 times, else check on thread id with a case!
  for (i = 0; i < 100; i++) {
    printf("%d\n", number);
  }

  return NULL;
}

int main(int argc, char** argv) {
  srand(time(NULL));

  int i, err;
  int rand_number = rand() % 100;

  for (i = 0; i < N_THREADS; i++) {
    err = pthread_create(&tid[i], NULL, &handleThread, &rand_number);

    if (err != 0) {
      printf("Can't create thread\n");
      exit(1);
    }
  }

  // wait until all created threads are terminated, before
  // continuing in calling thread (main thread)
  for (i = 0; i < N_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
