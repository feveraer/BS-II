#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  // make 3 child processes, each writing its process id to stdout
  pid_t children[3];
 
  // arguments for ./writestring call
  // terminate c-string with 0 (or NULL)
  char *arg_call[3] = {"/root/c/labo3/writestring", "hello", 0};

  if ((children[0] = fork()) == 0) {
    // first child stuff goes here
    printf("child 1 process id: %d\n", getpid());
    // execv(arg_call[0], arg_call);
    // todo: check if execl returns error
    execl("/root/c/labo3/writestring", "/root/c/labo3/writestring", "hello", (char*) 0);
    exit(0);
  }
  else {
    if ((children[1] = fork()) == 0) {
      // second child stuff goes here
      printf("child 2 process id: %d\n", getpid()); 
      //execv(arg_call[0], arg_call);
      execl("/root/c/labo3/writestring", "/root/c/labo3/writestring", "hello", (char*) 0);
      exit(0);
    }
    else if((children[2] = fork()) == 0) {
      // third child stuff goes here
      printf("child 3 process id: %d\n", getpid());
      //execv(arg_call[0], arg_call);
      execl("/root/c/labo3/writestring", "/root/c/labo3/writestring", "hello", (char*) 0);
      exit(0);
    }
  }
  // we are in the parent, we have the PIDs of our three
  // children in child1, child2, and child3
  
  // wait for children to terminate
  int i;
  for (i = 0; i < 3; i++) {
    waitpid(children[i], NULL, 0);
  }
  
  // wait for all children
  // waitpid(P_ALL, NULL, 0);

  for (i = 0; i < 3; i++) {
    printf("parent: child %d pid: %d\n", i+1, children[i]); 
  }

  return 0;
}
