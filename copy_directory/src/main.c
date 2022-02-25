#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "../include/copy_directory.h"

int
main (int argc, char* argv[])
{
	copy_directory(argv[1],argv[2]); // start_dir, destination_dir
	return 0;
}

