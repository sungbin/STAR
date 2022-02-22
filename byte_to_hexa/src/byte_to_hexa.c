#include <stdio.h>
#include <stdlib.h>

unsigned char*
byte_to_hexa (char * file_name) {

	FILE * file = fopen(file_name, "rb");

	// file size
	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	rewind(file);

	// malloc
	unsigned char* byte_arr = malloc(sizeof(unsigned char)*f_size);

	// read buffer
	fread(byte_arr, 1, f_size,  file);
	fclose(file);

	return byte_arr;	
}
