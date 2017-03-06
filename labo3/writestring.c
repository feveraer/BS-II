#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./writestring arg\n");
    exit(1);
  }

  printf("%d %s\n", getpid(), argv[1]);
  sleep(10); 
  return 0;
}
