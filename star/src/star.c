#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/star.h"

unsigned int file_no = 0;

void
_archive (char * target_dir, char * des_dir, char * sub_dir, FILE * star_fp);

void
archive (char * target_dir, char * star_path) {

	/*
	if (access(destinated_dir_path, F_OK) == 0) {
		fprintf(stderr, "destinated-file already exists");
		exit(1);
	}
	else if (! mkdir(destinated_dir_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) {
		fprintf(stderr, "mkdir fails: %s", destinated_dir_path);
		exit(1);
	}
	*/

	FILE * star_fp = fopen(star_path, "wb");
	
	// (1) - path recursive
	_archive (target_dir, "", "", star_fp);

	printf("len: %d, paths: %s\n", file_no, star_path);

	fclose(star_fp);
}

void
_archive (char * target_dir, char * des_dir, char * sub_dir, FILE * star_fp) {

	char * inner_dir_path;

	int sub_dir_len = strlen(sub_dir);
	if (sub_dir_len > 0) {

		int inner_dir_path_len = strlen(target_dir)+sub_dir_len+2;
		inner_dir_path = malloc(sizeof(char) * inner_dir_path_len);
		snprintf(inner_dir_path, inner_dir_path_len, "%s/%s", target_dir, sub_dir);
	
	}
	else {

		inner_dir_path = strdup(target_dir);

	}

        DIR * dp = opendir(inner_dir_path);
        struct dirent *ep;

        if (dp != NULL)
        {
                while ((ep = readdir(dp))) {
                        if (strcmp(ep->d_name,".") == 0) {
                                continue;
                        }
                        if (strcmp(ep->d_name,"..") == 0) {
                                continue;
                        }

			char * sub_child_dir;
			if (sub_dir_len > 0) {

				int sub_child_dir_len = strlen(sub_dir)+strlen(ep->d_name)+2;
				sub_child_dir = malloc(sizeof(char) * sub_child_dir_len);
				snprintf(sub_child_dir, sub_child_dir_len, "%s/%s", sub_dir, ep->d_name);

			}
			else {
				sub_child_dir = strdup(ep->d_name);
			}

			char * origin_path, * achiv_path;
			int origin_path_len, achiv_path_len; 

			origin_path_len = strlen(target_dir)+strlen(sub_child_dir)+2;
			achiv_path_len = strlen(des_dir)+strlen(sub_child_dir)+3;

			origin_path = malloc(sizeof(char) * origin_path_len);
			achiv_path = malloc(sizeof(char) * achiv_path_len);
			
			snprintf(origin_path, origin_path_len, "%s/%s", target_dir, sub_child_dir);
			snprintf(achiv_path, achiv_path_len, "%s/%s;", des_dir, sub_child_dir);

		

                        if (ep->d_type == DT_DIR) {

				_archive(origin_path, achiv_path, sub_dir, star_fp);
                        } 
			else {

					printf("origin-path: %s\n", origin_path);
					printf("target-path: %s\n", achiv_path);

				/*
				int buf = fwrite(achiv_path, 1, achiv_path_len+1, star_fp);
				printf("buf size: %d\n",buf);
				file_no += buf;
				buf = fwrite(";", 1, 1, star_fp);
				printf("buf size: %d\n",buf);
				file_no += buf;
				if (file_no > sizeof(unsigned int)) {
					fprintf(stderr, "too many files.\n");
					exit(1);
				}
				*/
			}

			free(sub_child_dir);
			free(origin_path);
			free(achiv_path);
                }
                closedir(dp);
        }
        else {

		fprintf(stderr, "Couldn't open the directory: %s \n", inner_dir_path);
                exit(1);

        }

	free(inner_dir_path);

}

void
list (char * star_path) {

}

void
extract (char * star_path) {

}

