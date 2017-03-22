#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000
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
  struct args *arguments = (struct args*) arg;

  printf("thread_id: %d\n", *(arguments->thread_id));
  if (*(arguments->thread_id) == 0) {
    printf("Smallest number: %.2f\n", smallest(arguments->tab));
  } else {
    printf("Biggest number: %.2f\n", biggest(arguments->tab));
  }
  // free(arguments->thread_id);
}

int main(int argc, char** argv) {
  float *tab = malloc(sizeof(*tab)*N);
  struct args *arguments = malloc(sizeof(*arguments));
  arguments->tab = tab;
  srand(time(NULL));
  int i, status;
  for (i = 0; i < N; i++) {
    tab[i] = ((float) rand()) / (RAND_MAX / N);
  }
  for (i = 0; i < N_THREADS; i++) {
    arguments->thread_id = malloc(sizeof(int));
    *(arguments->thread_id) = i;
    status = pthread_create(&tid[i], NULL, &handle_thread, arguments);

    if (status != 0) {
      perror("Can't create thread\n");
      exit(1);
    }
  }

  for (i = 0; i < N_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  free(tab);
  free(arguments);
  return 0;
}
