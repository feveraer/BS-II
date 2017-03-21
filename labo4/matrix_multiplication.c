#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 2
#define N 4

pthread_t tid[N_THREADS];
int tab1[N][N];
int tab2[N][N];
int tab_res[N][N];

// typedef struct args args;
// struct args {
//   int thread_id;
//   int* tab;
// };

void *handle_thread(void *arg) {
  int id = *((int *) arg);
  printf("handle_thread: %d\n", id);
  int i, j, k;
  for (i = 0 + id; i < N; i += N_THREADS) {
    for (j = 0; j < N; j++) {
      tab_res[i][j] = 0;
      for (k = 0; k < N; k++) {
        tab_res[i][j] += tab1[i][k] * tab2[k][j];
      }
    }
  }
  free(arg);
}

int main(int argc, char** argv) {
  // struct args arguments[N_THREADS];
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      tab1[i][j] = i + j;
      tab2[i][j] = i + j;
    }
  }

  printf("Original matrix:\n");

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d\t", tab1[i][j]);
    }
    printf("\n");
  }

  for (i = 0; i < N_THREADS; i++) {
    // arguments[i].thread_id = i;
    // arguments[i].tab = tab;
    int *arg = malloc(sizeof(*arg));
    *arg = i;
    pthread_create(&tid[i], NULL, &handle_thread, arg);
  }

  for (i = 0; i < N_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  printf("Result:\n");

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d\t", tab_res[i][j]);
    }
    printf("\n");
  }

  return 0;
}
