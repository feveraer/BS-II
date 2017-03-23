#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREADS 8
#define N 10

int number_tickets = N;
pthread_t tid[N_THREADS];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {

  int not_done = 1;
  int total_sold = 0;
  while (not_done){

    pthread_mutex_lock(&mtx);

    if (total_sold < number_tickets) {
      total_sold++;
      number_tickets--;
      sleep(rand() % 3);
      printf("thread %d: tickets to go %d\n", pthread_self(), number_tickets);
    } else {
      not_done = 0;
    }

    printf("thread %d: total sold %d\n", pthread_self(), total_sold);
    pthread_mutex_unlock (&mtx);
  }

  return NULL;

}

int main(int argc, char** argv) {
  int i;
  for (i = 0; i < N_THREADS; i++) {
    pthread_create(&tid[i], NULL, &worker, NULL);
  }

  for (i = 0; i < N_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  // for (i = 0; i < N_THREADS; i++) {
  //   printf("thread %d - sold tickets: %d\n", i, (int) *sold_tickets);
  //   sold_tickets++;
  // }

  pthread_mutex_destroy(&mtx);
  return 0;
}
