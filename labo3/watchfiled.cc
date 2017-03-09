#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char **argv) {

  std::ifstream watchfile("/root/c/labo3/watchfile.txt");
  const char* watch = "/root/c/labo2/watchfile";
  std::map<std::string, bool> is_watched_map;
  std::string single;

  // read file to get all files that need to be watched,
  // initialize map that nothing is being watched yet
  // not necessary
  // while (watchfile && getline(watchfile, single)) {
  //   is_watched_map[single] = false;
  // }

  while(1) {
    while (getline(watchfile, single)) {
      is_watched_map[single] = false;
      if (!is_watched_map[single]) {
        if (fork() == 0) {
          execl(watch, watch, single.c_str(), (char*) 0);
          is_watched_map[single] = true;
        }
      }
      watchfile.clear(); // clear EOF flag
      watchfile.seekg(0, std::ios::beg);

      // delay for 1 second
      sleep(1);
    }
  }
  return 0;
}
