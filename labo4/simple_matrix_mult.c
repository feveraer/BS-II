#include <stdio.h>
#include <stdlib.h>

#define N 4

int main(int argc, char** argv) {
  // int tab1[N][N] = {{2,3}, {4,5}};
  // int tab2[N][N] = {{1,2}, {3,4}};

  int tab1[N][N];
  int tab2[N][N];
  int tab_res[N][N];

  int i, j, k;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      tab1[i][j] = i + j;
      tab2[i][j] = i + j;
    }
  }
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      tab_res[i][j] = 0;
      for (k = 0; k < N; k++) {
        tab_res[i][j] += tab1[i][k] * tab2[k][j];
      }
    }
  }

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%d\t", tab_res[i][j]);
    }
    printf("\n");
  }
}
