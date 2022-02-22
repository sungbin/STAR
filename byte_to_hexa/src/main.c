#include <stdio.h>
#include <stdlib.h>

#include "../include/byte_to_hexa.h"

int
main (int argc, char* argv[]) {

	char* input_f_name = argv[1];
	char* output_f_name = argv[2];

	FILE * input_fp = fopen(input_f_name, "r");

	long f_size = byte_to_hexa(input_f_name, output_f_name);
	
	printf("\nbyte size: %ld \n",f_size);

	fclose(input_fp);

	return 0;
}

