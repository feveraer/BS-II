#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>

int main() {
  int file_input_desc = open("a-z_10mb.txt", O_RDONLY);
  int file_output_desc;
  char output_buffer[22] = "temp_10mb_buffer_";
  int output_size = 10485760;

  int i;
  for (i = 1; i <= 8192; i*=2) {
    char buffer[i];
    sprintf(output_buffer, "temp_10mb_buffer_%d", i);
    file_output_desc = open(output_buffer, O_WRONLY | O_CREAT | O_APPEND); 

    double start = clock();
    int written_bytes = 0;
    do {
      written_bytes += write(file_output_desc, buffer, i);
    } while ( written_bytes < output_size);

    double time = (clock() - start)/CLOCKS_PER_SEC;
    printf("BUF_SIZ=%d\tTime=%.5f\n", i, time);

    unlink(output_buffer);
  }

  return 0;
}
