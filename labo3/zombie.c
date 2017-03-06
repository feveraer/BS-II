#include <unistd.h>

int main(int argc, char **argv) {
  int pid;
  if ((pid = fork()) == 0) {
    // child
    sleep(5);
  } else {
    // parent
    sleep(20);
  }
  return 0;
}
