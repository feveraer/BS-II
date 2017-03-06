#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void filecopy(int ifd, int ofd) {
  int n;
  char buf[BUFSIZ];

  while((n = read(ifd, buf, BUFSIZ)) > 0) {
    if (write(ofd, buf, n) != n) {
      perror("write error\n");
      exit(1);
    }
  }
}

int main(int argc, char **argv) {
  int fd;

  // no arguments, cat from STDIN
  if (argc == 1) {
    filecopy(STDIN, STDOUT);
  }
  else {
    while (--argc > 0) {
      if (strcmp(*++argv, "-") == 0) {
        filecopy(STDIN, STDOUT);
        argv += 1; 
      }
      if (*argv == NULL) { exit(0); }
      if((fd = open(*argv, O_RDONLY)) < 0) {
        fprintf(stderr, "couldn't open %s\n", *argv);
    	exit(1);
      }
      else {
        //fprintf(stdout, "read %s\n", *argv);
        filecopy(fd, STDOUT);
        close(fd);
      }
    }
  }
  return 0;
}
