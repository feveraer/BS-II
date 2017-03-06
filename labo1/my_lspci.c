#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <errno.h>

int
main(int argc, char** argv){
  
  if (iopl(3) < 0) {
    perror(argv[0]);
    exit(1);
  }

  int busnummer;
  int devicenummer;
  int functienummer;

  for (busnummer = 0; busnummer < 256; busnummer++) {
    for (devicenummer = 0; devicenummer < 32; devicenummer++) {
      for (functienummer = 0; functienummer < 7; functienummer++) {
        unsigned int getal = (1 << 31) + (busnummer << 16) + (devicenummer << 11) + (functienummer << 8);
	outl(getal, 0xcf8);
	unsigned int result = inl(0xcfc);
        if (result != 0xffffffff) {
	  int device_res = result >> 16;
	  int vendor_res = result & 0x0000ffff;
	  printf("BDF:%x:%x:%x vendor:%x device:%x\n", busnummer, devicenummer, functienummer, vendor_res, device_res);
	}
      }
    }
  }
  

  return 0;
}
