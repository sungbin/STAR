#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/star.h"

void
print_usage();

int
main (int argc, char* argv[])
{

	if (argc < 3) {
		print_usage();
		exit(1);
	}

	if (strcmp(argv[1], "archive") == 0) {
		archive(argv[2], argv[3]);
	}
	else if (strcmp(argv[1], "list") == 0) {
		list(argv[2]);
	}
	else if (strcmp(argv[1], "extract") == 0) {
		extract(argv[3]);
	}
	else {
		print_usage();
		exit(1);
	}

	return 0;
}

void
print_usage() {
	fprintf(stderr, "USAGE:\n");
	fprintf(stderr, "star archive <star-file-name> <destinated directory-path>\n");
	fprintf(stderr, "star list <star-file-name>\n");
	fprintf(stderr, "star extract <star-file-name>\n");
}
