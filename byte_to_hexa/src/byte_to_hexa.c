#include <stdio.h>
#include <stdlib.h>

#include "../include/byte_to_hexa.h"

long
byte_to_hexa (char * input_f_name, char * output_f_name) {

	FILE * input_fp = fopen(input_f_name, "rb");
	FILE * output_fp = fopen(output_f_name, "w");

	long f_size = 0;
	
	while ( 1 ) {

		unsigned char in_buf[512];
		int buf_size = fread(in_buf, 1, 512, input_fp);

		f_size = f_size + buf_size;
	
		for (int _idx = 0; _idx < buf_size; _idx = _idx+1) {
			if (_idx % 16 == 0) {
				fprintf(output_fp, "\n");
			}

			fprintf(output_fp, "%02x", in_buf[_idx]);

			if (_idx % 2 == 1) {
				fprintf(output_fp, " ");
			}
		}

		if (buf_size < 512) {
			break;
		}
	}
	fprintf(output_fp, "\n");

	fclose(input_fp);
	fclose(output_fp);

	return f_size;
}
