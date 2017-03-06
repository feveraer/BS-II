#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
  int filedesc = open("a-z_10mb.txt", O_WRONLY | O_CREAT | O_APPEND);
  int size = 10485760;

  if (filedesc < 0) {
    perror(argv[0]);
    exit(1);
  } 
 
  int i;
  char randomletter[1] = ""; 
  for (i = 0; i < size; i++) {
    randomletter[0] = 'a' + (random() % 26);
    if (write(filedesc, randomletter, 1) != 1) {
      perror(argv[0]);
    }
  }

  // ook nog checken op fout
  close(filedesc);
  return 0;
}

