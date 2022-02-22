#include <stdio.h>
#include <stdlib.h>

#include "../include/byte_to_hexa.h"

int
main (int argc, char* argv[]) {

	char* f_name = argv[1];
	File * file = fopen(f_name,"rb");
	byte_to_hexa(file);

/*

	char* f_name = argv[1];
	unsigned char* byte_arr = byte_to_hexa(f_name);
	unsigned long long b_size = (long)sizeof(byte_arr) / sizeof(unsigned char);

	printf("byte size: %lld \n",b_size);

	for (long _idx = 0; _idx < b_size; _idx = _idx+1) {

		printf("%02X ", byte_arr[_idx]);
	}
*/
}

