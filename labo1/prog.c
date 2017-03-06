#include <stdio.h>
#include <stdlib.h>

int
main(){
  int *p_array;
  p_array = (int *)malloc(sizeof(int)*2000);

  int i;
  for(i=0; i < 2000; i++) {
    p_array[i] = i;
  }

  for(i=0; i < 2000; i++) {
    printf("%d\n",p_array[i]);
  }

  // free allocated memory to prevent leak
  free(p_array);
  return 0;
}
