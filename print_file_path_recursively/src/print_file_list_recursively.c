#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "../include/print_file_list_recursively.h"

void
print_file_list (char * start_dir) {

	DIR *dp = opendir(start_dir);
	print_file_list_recursive(dp, start_dir);	
}

void 
print_file_list_recursive (DIR *dp, char * parrent_dir) {

	struct dirent *ep;
	if (dp != NULL)
	{
		while (ep = readdir (dp)) {
			if (strcmp(ep->d_name,".") && strcmp(ep->d_name,".."))
				puts (ep->d_name);

			if (ep->d_type == DT_DIR && strcmp(ep->d_name,".") && strcmp(ep->d_name,"..")) {
				char inner_dir[4096];
				strcpy(inner_dir, parrent_dir);
				strcat(inner_dir, ep->d_name);
				
				printf("ENTER: %s\n", inner_dir);
				DIR *dp2 = opendir (inner_dir);
				print_file_list_recursive(dp2, inner_dir);
			}
		}
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");
}
