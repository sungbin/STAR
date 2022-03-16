#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <libgen.h>

#include "../include/star.h"

unsigned int file_no = 0;
unsigned int data_size = 0;

void
archive_path (char * target_dir, char * des_dir, char * sub_dir, FILE * p_fp, FILE * d_fp);

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

	char * path_name = ".path";
	FILE * p_fp = fopen(path_name, "wb");
	char * data_name = ".data";
	FILE * d_fp = fopen(data_name, "wb");


	archive_path(target_dir, basename(target_dir), "", p_fp, d_fp);
	fclose(p_fp);
	fclose(d_fp);

	int buf_size = fwrite(&file_no, 1, 4, star_fp);
	
	p_fp = fopen(path_name, "rb");
	buf_size = 0;
	do {
		char buf[512];
		buf_size = fread(buf, 1, 512, p_fp);
		fwrite(buf, 1, buf_size, star_fp);

	} while(buf_size > 0);
	fclose(p_fp);

	fwrite(&data_size, 1, 4, star_fp);

	d_fp = fopen(data_name, "rb");
	buf_size = 0;
	do {
		char buf[512];
		buf_size = fread(buf, 1, 512, d_fp);
		fwrite(buf, 1, buf_size, star_fp);
	} while(buf_size > 0);
	fclose(d_fp);

	fclose(star_fp);
	remove(data_name);
	remove(path_name);
	
	printf("ARCHIVE: %s (file_no: %u, data-size: %u)\n", star_path, file_no, data_size);

}

void
archive_path (char * target_dir, char * des_dir, char * sub_dir, FILE * p_fp, FILE * d_fp) {

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
			snprintf(achiv_path, achiv_path_len, "%s/%s", des_dir, sub_child_dir);

                        if (ep->d_type == DT_DIR) {

				archive_path(origin_path, achiv_path, sub_dir, p_fp, d_fp);
                        } 
			else {

				int b_size = fwrite(strcat(achiv_path, ";"), 1, strlen(achiv_path)+1, p_fp);
				file_no += b_size;
				if (file_no > (UINT_MAX)) {
					fprintf(stderr, "too many files. (%d)\n", file_no);
					exit(1);
				}

				FILE * fp = fopen(origin_path, "rb");
				int fd = fileno(fp);
        			struct stat _stat;
        			fstat(fd, &_stat);
				off_t f_size = _stat.st_size;
				data_size += f_size;

				b_size = 0;
				do {
					char buf[512];
					b_size = fread(buf, 1, 512, fp);
					b_size = fwrite(buf, 1, b_size, d_fp);

				} while (b_size > 0);

				fclose(fp);
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
	
	if (access(star_path, F_OK) == 1) {
		fprintf(stderr, "target star file not exists\n");
		exit(1);
	}

	FILE * s_fp = fopen(star_path, "rb");
	
	unsigned int path_n;
	fread(&path_n, 1, 4, s_fp);

	int b_size = 0;

	do {
		char buf[512];
		if (path_n > 512) {
			b_size = fread(buf, 1, 512, s_fp);
			path_n -= b_size;
		}
		else {
			b_size = fread(buf, 1, path_n, s_fp);
			path_n -= b_size;
		}

		int b_b = 0;
		while (b_b < b_size) {
			if(buf[b_b] == ';') {
				printf("\n");
			}
			else {
				printf("%c", buf[b_b]);
			}
			b_b++;
		}

	} while (path_n > 0);

	fclose(s_fp);
}

void
extract (char * star_path) {
	/*
	if (access(star_path, F_OK) == 1) {
		fprintf(stderr, "target star file not exists\n");
		exit(1);
	}

	char * path_name = ".path";
	FILE * p_fp = fopen(path_name, "wb");

	FILE * s_fp = fopen(star_path, "rb");
	
	unsigned int path_n;
	fread(&path_n, 1, 4, s_fp);
	fwrite(&path_n, 1, 4, p_fp);

	int b_size = 0;
	do {
		char buf[512];
		b_size = fread(buf, 1, 512, s_fp);
		b_size = fwrite(buf, 1, b_size, p_fp);
		path_n -= b_size;

	} while (path_n > 0);
	fclose(p_fp);

	unsigned int data_size;
	fread(&data_size, 1, 4, s_fp);

	do {
		char buf[512];
		b_size = fread(buf, 1, 512, s_fp);

		

		data_size -= b_size;

	} while (data_size > 0);

	fclose(s_fp);
	*/
}

