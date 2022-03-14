#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/copy_directory.h"

void
copy_directory (char * target_dir, char * destinated_dir) {

	// check if [destinated, start] directories exist or not
	if (access(target_dir, F_OK) == -1) {
		fprintf(stderr, "target-directory not exists");
		exit(1);
	}
	if (access(destinated_dir, F_OK) == 0) {
		fprintf(stderr, "destinated-directory already exists");
		exit(1);
	}

	if (mkdir(destinated_dir, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1) {

                        fprintf(stderr, "fail to mkdir: %s\n\n", destinated_dir);
                        exit(1);

	}

	path_recursive(target_dir, destinated_dir, "", &copy);

}

void
copy (char * origin_path, char * copied_path, int is_dir) {
	
	printf("origin: %s\n", origin_path);
	printf("copied: %s\n\n", copied_path);

	if (access(origin_path, F_OK) == -1) {
		fprintf(stderr, "target-directory not exists: %s\n\n", origin_path);
		exit(1);
	}

	if (access(copied_path, F_OK) == 0) {
		fprintf(stderr, "destinated-directory already exists: %s\n\n", copied_path);
		exit(1);
	}

	if (is_dir) {

		// mkdir 755
		if (mkdir(copied_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1) {

			fprintf(stderr, "fail to mkdir: %s\n\n", copied_path);
			exit(1);

		}

	}
	else {

		FILE * in_fp = fopen(origin_path, "rb");
		FILE * out_fp = fopen(copied_path, "wb");

		long f_size = 0;
		
		while ( 1 ) {

			unsigned char in_buf[512];
			int buf_size = fread(in_buf, 1, 512, in_fp);
			f_size = f_size + buf_size;
	
			fwrite(in_buf, 1, buf_size, out_fp);

			if (buf_size < 512) {

				break;

			}
			
		}

	}

}

void
path_recursive (char * target_dir, char * destinated_dir, char * sub_dir, void (*copy)(char*, char*, int)) {

	char * inner_dir_path;

	int sub_dir_len = strlen(sub_dir);
	if(sub_dir_len > 0) {

		int inner_dir_path_len = strlen(target_dir)+sub_dir_len+2;
		inner_dir_path = malloc(sizeof(char) * inner_dir_path_len);
		snprintf(inner_dir_path, inner_dir_path_len, "%s/%s", target_dir, sub_dir);
	
	}
	else {

		inner_dir_path = strdup(target_dir);

	}

        DIR * dp = opendir(inner_dir_path);
        struct dirent *ep;

        if (dp != NULL) {
                while (ep = readdir(dp)) {
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

			char * origin_path, * copied_path;
			int origin_path_len, copied_path_len; 

			origin_path_len = strlen(target_dir)+strlen(sub_child_dir)+2;
			copied_path_len = strlen(destinated_dir)+strlen(sub_child_dir)+2;

			origin_path = malloc(sizeof(char) * origin_path_len);
			copied_path = malloc(sizeof(char) * copied_path_len);
			
			snprintf(origin_path, origin_path_len, "%s/%s", target_dir, sub_child_dir);
			snprintf(copied_path, copied_path_len, "%s/%s", destinated_dir, sub_child_dir);

			(*copy)(origin_path, copied_path, ep->d_type == DT_DIR);

                        if (ep->d_type == DT_DIR) {

                                path_recursive(target_dir, destinated_dir, sub_child_dir, copy);

                        } 

			free(sub_child_dir);
			free(origin_path);
			free(copied_path);
                }
                closedir(dp);
        }
        else {

		fprintf(stderr, "Couldn't open the directory: %s \n", inner_dir_path);
                exit(1);

        }

	free(inner_dir_path);

}
