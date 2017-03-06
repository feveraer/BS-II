#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
  // 1 command line argument needs to be provided
  if (argc != 2) {
    fprintf(stderr, "usage: ./watchfile file\n");
    exit(1);
  }

  // argument needs to be a file
  struct stat file_stat;
  stat(*++argv, &file_stat);
  // S_ISREG(mode) returns 0 if test is false, non-zero if true
  if (S_ISREG(file_stat.st_mode) == 0) {
    fprintf(stderr, "provided argument needs to be a regular file\n");
    exit(1);
  }

  // get current modification time of file
  time_t curr_time = file_stat.st_mtime;

  // watch over file and report if changes were made
  int err;
  while(1) {
    err = stat(*argv, &file_stat);
    if (err != 0) {
      perror("file was modified");
      exit(errno);
    }
    if (file_stat.st_mtime > curr_time) {
      curr_time = file_stat.st_mtime;
      printf("File %s was changed!\n", *argv);
    }
  }
  return 0;
}
