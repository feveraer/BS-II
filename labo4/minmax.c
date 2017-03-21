#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000000
#define N_THREADS 2

pthread_t tid[N_THREADS];

typedef struct args args;
struct args {
  int *thread_id;
  float *tab;
};


float smallest(float *tab) {
  int i;
  float smallest = tab[0];
  for (i = 1; i < N; i++) {
    if (tab[i] < smallest) {
      smallest = tab[i];
    }
  }
  return smallest;
}

float biggest(float *tab) {
  int i;
  float biggest = tab[0];
  for (i = 1; i < N; i++) {
    if (tab[i] > biggest) {
      biggest = tab[i];
    }
  }
  return biggest;
}

void *handle_thread(void *arg) {
  struct args *arguments = (struct args*)arg;

  if (arguments->thread_id == 0) {
    printf("Smallest number: %.2f\n", smallest(arguments->tab));
  } else {
    printf("Biggest number: %.2f\n", biggest(arguments->tab));
  }
}

int main(int argc, char** argv) {
  float *tab = malloc(sizeof(*tab)*N);
  struct args arguments;
  arguments.tab = tab;
  srand(time(NULL));
  int i, status;
  for (i = 0; i < N; i++) {
    tab[i] = ((float) rand()) / RAND_MAX;
  }
  for (i = 0; i < N_THREADS; i++) {
    int *thread_id = malloc(sizeof(*thread_id)); 
    *thread_id = i;
    arguments.thread_id = thread_id;
    status = pthread_create(&tid[i], NULL, &handle_thread, (void*)&arguments);

    if (status != 0) {
      perror("Can't create thread\n");
      exit(1);
    }
  }

  for (i = 0; i < N_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  free(tab);
  return 0;
}
