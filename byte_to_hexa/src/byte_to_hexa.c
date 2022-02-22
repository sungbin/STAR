#include <stdio.h>
#include <stdlib.h>

//long int sh (char* buffer, char * file_name);
long int msb (char* buffer, long int buffer_len, char * file_name);

long int
byte_to_hexa (char* byte_buf, long int buf_len, char * file_name) {

	return msb(byte_buf, buf_len, file_name);
}

long int msb (char* byte_buf, long int f_size, char * file_name) {

	FILE * file = fopen(file_name, "rb");

	// file size
	// fseek(file, 0, SEEK_END);
	// long int f_size = ftell(file);
	// rewind(file);

	// malloc
	//byte_buf = (char*)malloc(sizeof(char)*f_size);

	// read buffer
	fread(byte_buf, 1, f_size, file);
	fclose(file);

	return f_size;	
}
