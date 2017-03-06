#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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
  // 2 command line arguments need to be provided
  if (argc != 3) {
    fprintf(stderr, "usage: ./my_cp source destination\n");
    exit(1);
  }

  // arguments need to be files
  struct stat source_stat, dest_stat;
  stat(*++argv, &source_stat);
  stat(*++argv, &dest_stat);
  if (S_ISDIR(source_stat.st_mode) || S_ISDIR(dest_stat.st_mode)) {
    fprintf(stderr, "source and/or destination can't be directories\n");
    exit(1);
  }

  // create input fd
  int ifd = open(*--argv, O_RDONLY);
  if (ifd < 0) {
    fprintf(stderr, "couldn't open %s\n", *argv);
    exit(1);
  }
  // create output fd
  int ofd = open(*++argv, O_WRONLY | O_CREAT);
  if (ofd < 0) {
    fprintf(stderr, "couldn't open %s\n", *argv);
    exit(1); 
  }

  // copy
  filecopy(ifd, ofd);
  close(ifd);
  close(ofd);
 
  return 0;
}
