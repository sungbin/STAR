#include <stdio.h>
#include <stdlib.h>

#include "../include/byte_to_hexa.h"

hexa_data
byte_to_hexa (char * file_name) {

	FILE * file = fopen(file_name, "rb");
	long int f_size;

	// file size
	fseek(file, 0, SEEK_END);
	f_size = ftell(file);
	rewind(file);

	// malloc
	char * byte_buf = (char*)malloc(sizeof(char)*f_size);

	// read buffer
	fread(byte_buf, 1, f_size, file);
	fclose(file);

	hexa_data data = { .len = f_size, .data = byte_buf };

	return data;
}
