#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
 
  int filedesc = open("a-z_10mb.txt", O_RDONLY); 
  int i;
  for (i = 1; i <= 8192; i*=2) {
    //todo: check for error -> call perror()
    //int filedesc = open("a-z_10mb.txt", O_RDONLY);
    char buffer[i];
    double start = clock();
    while(read(filedesc, buffer, i) == i) {}
    double time = (clock() - start)/CLOCKS_PER_SEC;
    printf("BUF_SIZ=%d\tTime=%.2f\n", i, time);
   
    //reset offset
    lseek(filedesc, 0, SEEK_SET);
  } 

  return 0;
}
