#include <stdio.h>
#include <stdlib.h>

#include "../include/byte_to_hexa.h"

int
main (int argc, char* argv[]) {

	char* f_name = argv[1];
	char* byte_arr;

	FILE * file = fopen(f_name, "rb");
	fseek(file, 0, SEEK_END);
	long int f_size = ftell(file);
	rewind(file);
	byte_arr = (char*)malloc(sizeof(char)*f_size);

	//long int b_size = byte_to_hexa(byte_arr, f_name);
	byte_to_hexa(byte_arr, f_size, f_name);

	for (long int _idx = 0; _idx < f_size; _idx = _idx+1) {
		if(_idx % 16 == 0) {
			printf("\n");
		}
		printf("%02x", (unsigned char)byte_arr[_idx]);
		if(_idx % 2 == 1) {
			printf(" ");
		}
	}
//	free(byte_arr);
	printf("\nbyte size: %ld \n",f_size);
}


long int sb (char* byte_buf, long int f_size, char * file_name) {

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

