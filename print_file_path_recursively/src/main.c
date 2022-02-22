#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "../include/print_file_list_recursively.h"

int
main (int argc, char* argv[])
{
	print_file_list(argv[1]);
}

