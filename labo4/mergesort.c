#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 20

void merge(int *tab, int n) {
  int i, j, nL;

  // right half biggest in case of odd size
  nL = n/2;
  // no need to keep track of right half size, we
  // only need nL and n for it
  // nR = (n % 2 == 0) ? n/2 : n/2 + 1;
  
  // copy contents of tab to H(elp) array
  int H[n];
  for (i = 0; i < n; i++) {
    H[i] = *tab;
    tab++;
  }

  // left and right halves indices
  i = 0;
  j = nL;
  // decrement tab pointer again to where it pointed to
  // before the copy operation
  tab -= n;

  // merge from H back to tab
  while (i < nL && j < n) {
    if (H[i] <= H[j]) {
      *tab = H[i];
      i++;
    } else {
      *tab = H[j];
      j++;
    }
    tab++;
  }

  // copy remaining elements of H, if there are any
  // left half first
  while (i < nL) {
    *tab = H[i];
    i++;
    tab++;
  }

  while (j < n) {
    *tab = H[j];
    j++;
    tab++;
  }
}

void sort (int *tab, int n){
  if (n>1){
    /* sorteer linkerhelft */
    sort (tab,n/2);
    /*sorteer rechterhelft*/
    sort (tab+n/2,n-n/2);
    merge(tab,n);
  }
}

void print_tab(int *tab, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", tab[i]);
    printf("\n");
  }
}

void fill_tab(int *tab, int n) {
  int i;
  for (i = n; i > 0; i--) {
    *tab = i;
    tab++;
  }
}

int main(int argc, char** argv) {
  int tab[N];
  fill_tab(tab, N);
  // int n = sizeof(tab) / sizeof(*tab);

  printf("Unsorted array: \n");
  print_tab(tab, N);

  sort(tab, N);

  printf("Sorted array: \n");
  print_tab(tab, N);

  return 0;
}

