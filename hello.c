#include	<stdlib.h>
#include    <stdio.h>

int main ( int argc, char *argv[] ) {
  // prioriteit van stdout hoger gezet
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("Hello ");
  fprintf(stderr, "ERROR");
  printf(" World\n");
  return EXIT_SUCCESS;
}
