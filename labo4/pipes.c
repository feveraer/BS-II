#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
  pid_t pid;
  if (argc!=2){
    printf("One argument expected!\n");
    exit(1);
  }
  else {
    int fd[2];
    int i;
    int size = atoi(argv[1]);
    for(i=0;i<size;i++){
      if (pipe(fd)<0){
        perror(argv[0]);
        exit(1);
      }
      if ((pid=fork())<0){
        perror(argv[0]);
      }
      if (pid==0){
        // child process
        close(fd[0]);
        srand(getpid());
        int number=rand();
        if ((write(fd[1],&number,sizeof(int))!=sizeof(int))<0){
          perror(argv[0]);
          exit(1);
        }
        exit(0);
      }
      else {
        // parent process
        close(fd[1]);
        // wait until child process is closed
        if (waitpid(pid, NULL, 0) == pid){
          int number;
          read(fd[0],&number,sizeof(int));
          printf("pid=%d value=%d!\n",pid,number);
        }
      }
    }
  }
  return 0;
}
