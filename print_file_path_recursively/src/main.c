#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "../include/print_file_list_recursively.h"

int
main (int argc, char* argv[])
{
	print_path_recursive(argv[1]);
	return 0;
}

