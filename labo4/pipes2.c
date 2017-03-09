#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

struct process {
  int number;
  int pid;
  int fd_write;
};

int main(int argc, char **argv){
  pid_t pid;
  pid_t wpid;

  if (argc!=2){
    printf("One argument expected!\n");
    exit(1);
  } else {
    int fd[2];
    int fd_response[2];
    int i;
    struct process processes[atoi(argv[1])];
    int counter = 0;

    for(i=0;i<atoi(argv[1]);i++){
      // Create first pipe to send the numbers
      if (pipe(fd)<0){
        perror(argv[0]);
        exit(1);
      }

      // Create second pipe to send the response
      if (pipe(fd_response)<0) {
        perror(argv[0]);
        exit(1);
      }

      // Create fork, check on error
      if ((pid=fork())<0){
        perror(argv[0]);
      }

      // Child process
      if (pid==0){
        // Close read end of pipe, we only write in the child
        close(fd[0]);
        close(fd_response[1]);

        // Generate random number
        srand(getpid());
        int number=rand();

        // Write the random number on the pipe
        if (write(fd[1],&number,sizeof(int))!=sizeof(int)){
          perror(argv[0]);
          exit(1);
        }

        // Wait on the response
        struct process winner;
        if (read(fd_response[0],&winner,sizeof(struct process)) != sizeof(struct process)) {
          exit(1);
        }

        // printf("child: %d says: winner is: %d with pid: %d\n", getpid(), winner.number, winner.pid);

        if (getpid() == winner.pid) {
          printf("I'm the winner!\n");
        } else {
          printf("Process %d is the winner\n", winner.pid);
        }

        // When done writing, kill child
        exit(0);
      }
      // Parent process 
      else {
        close(fd[1]); // Close writing end of the pipe
        close(fd_response[0]); // Close reading pipe

        // Read the number from the pipe and displays it
        int number;
        read(fd[0],&number, sizeof(int));
        printf("pid=%d value=%d!\n",pid,number);

        struct process mp;
        mp.number = number;
        mp.pid = pid;
        mp.fd_write=fd_response[1];

        processes[counter].number = mp.number;
        processes[counter].pid = mp.pid;
        processes[counter].fd_write = fd_response[1];

        // Increment created children
        counter++;
      }
    }

    // Find max
    struct process max;
    max = processes[0];

    for (i = 1; i < atoi(argv[1]); i++) {
      if (processes[i].number > max.number) {
        max = processes[i];
      }
    }

    // Found max, send it to the child
    for (i = 0; i < atoi(argv[1]); i++) {
      if (write(processes[i].fd_write,&max,sizeof(struct process)) != sizeof(struct process)) {
        perror(argv[0]);
        exit(0);
      }
    }

    printf("\n");
    // printf("max number is: %d\n", max);

    // Wait on all the childs to exit
    while ((wpid = wait(0)) > 0)
    {
      // printf("Exited child %d succesfully\n", (int)wpid);
    }
  }

  return 0;
}
