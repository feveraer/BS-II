#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000000
#define N_THREADS 2

float rand_numbers[N];
pthread_t tid[N_THREADS];

float smallest() {
  int i;
  float smallest = rand_numbers[0];
  for (i = 1; i < N; i++) {
    if (rand_numbers[i] < smallest) {
      smallest = rand_numbers[i];
    }
  }
  return smallest;
}

float biggest() {
  int i;
  float biggest = rand_numbers[0];
  for (i = 1; i < N; i++) {
    if (rand_numbers[i] > biggest) {
      biggest = rand_numbers[i];
    }
  }
  return biggest;
}

void *handle_thread(void *arg) {
  int id = *(int*) arg;

  if (id == 0) {
    printf("Smallest number: %.2f\n", smallest());
  } else {
    printf("Biggest number: %.2f\n", biggest());
  }
}

int main(int argc, char** argv) {
  srand(time(NULL));
  int i, status;
  for (i = 0; i < N; i++) {
    rand_numbers[i] = ((float) rand()) / RAND_MAX;
  }
  for (i = 0; i < N_THREADS; i++) {
    status = pthread_create(&tid[i], NULL, &handle_thread, &i);

    if (status != 0) {
      perror("Can't create thread\n");
      exit(1);
    }
  }

  for (i = 0; i < N_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
