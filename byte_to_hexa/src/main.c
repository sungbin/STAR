#include <stdio.h>
#include <stdlib.h>

#include "../include/byte_to_hexa.h"

int
main (int argc, char* argv[]) {

	char* f_name = argv[1];

	char* byte_arr;
	long int f_size;

	hexa_data data = byte_to_hexa(f_name);
	f_size = data.len;
	byte_arr = data.data;

	for (long int _idx = 0; _idx < f_size; _idx = _idx+1) {
		if(_idx % 16 == 0) {
			printf("\n");
		}
		printf("%02x", (unsigned char)byte_arr[_idx]);
		if(_idx % 2 == 1) {
			printf(" ");
		}
	}
	free(byte_arr);
	printf("\nbyte size: %ld \n",f_size);
}

