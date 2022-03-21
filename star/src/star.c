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

int
mkdirs (char * dir_path);

char *
parent_dir (char * dir_path);

//int file_no = 0;
//unsigned int data_size = 0;

void
archive_path (char * target_dir, char * des_dir, char * sub_dir, FILE * s_fp);

void
archive (char * target_dir, char * star_path) {

	FILE * star_fp = fopen(star_path, "wb");
	archive_path(target_dir, basename(target_dir), "", star_fp);
	fclose(star_fp);

//	printf("ARCHIVE: %s (file_no: %d, data-size: %u)\n", star_path, file_no, data_size);

}

void
archive_path (char * target_dir, char * des_dir, char * sub_dir, FILE * s_fp) {

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
			unsigned int origin_path_len, achiv_path_len; 

			origin_path_len = strlen(target_dir)+strlen(sub_child_dir)+2;
			achiv_path_len = strlen(des_dir)+strlen(sub_child_dir)+2;

			origin_path = malloc(sizeof(char) * origin_path_len);
			achiv_path = malloc(sizeof(char) * achiv_path_len);
			
			snprintf(origin_path, origin_path_len, "%s/%s", target_dir, sub_child_dir);
			snprintf(achiv_path, achiv_path_len, "%s/%s", des_dir, sub_child_dir);

                        if (ep->d_type == DT_DIR) {

				archive_path(origin_path, achiv_path, sub_dir, s_fp);
                        } 
			else {

				// (1) file path
				achiv_path_len = strlen(achiv_path);
				int b_size;
				b_size = fwrite(&achiv_path_len, 1, 4, s_fp);
				b_size = fwrite(achiv_path, 1, achiv_path_len, s_fp);

// 				file_no ++;

				// (2) file data
				FILE * fp = fopen(origin_path, "rb");
				int fd = fileno(fp);
        			struct stat _stat;
        			fstat(fd, &_stat);
				off_t f_size = _stat.st_size;
// 				data_size += f_size;

				unsigned int uf_size = (unsigned int) f_size;
				b_size = fwrite(&uf_size, 1, 4, s_fp);

				b_size = 0;
				do {
					char buf[512];
					b_size = fread(buf, 1, 512, fp);
					//TODO: if-state, break
					b_size = fwrite(buf, 1, b_size, s_fp);

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
	do {	
		unsigned int path_n;
		int b_size = fread(&path_n, 1, 4, s_fp); //advise: can use fgetc()
		if (b_size != 4) {
			break;
		}
	
		char * file_path = malloc(path_n * sizeof(char));
		// strcpy(file_path, "");
		do {
			char buf[512];
			if (path_n > 512) {
				b_size = fread(buf, 1, 512, s_fp);
			}
			else {
				b_size = fread(buf, 1, path_n, s_fp);
			}
			strncat(file_path, buf, b_size);
			path_n -= b_size;

		} while (path_n > 0);

		unsigned int data_s;
		b_size = fread(&data_s, 1, 4, s_fp);
		if (b_size != 4) {
			fprintf(stderr, "cannot read data with %s\n", file_path);
			exit(1);
		}
	
		printf("%s\n", file_path);
		do {
			char buf[512];
			if (data_s > 512) {
				b_size = fread(buf, 1, 512, s_fp);
			}
			else {
				b_size = fread(buf, 1, data_s, s_fp);
			}
			data_s = data_s - ((unsigned int)b_size);
		} while (data_s > 0);
		free(file_path);

	} while (1);

	fclose(s_fp);

}


void
extract (char * star_path) {
	if (access(star_path, F_OK) == 1) {
		fprintf(stderr, "target star file not exists\n");
		exit(1);
	}

	FILE * s_fp = fopen(star_path, "rb");
	do {	
		unsigned int path_n;
		int b_size = fread(&path_n, 1, 4, s_fp);
		if (b_size != 4) {
			break;
		}
	
		char * file_path = malloc(path_n * sizeof(char)+2);
		strcpy(file_path, "./");
		do {
			char buf[512];
			if (path_n > 512) {
				b_size = fread(buf, 1, 512, s_fp);
			}
			else {
				b_size = fread(buf, 1, path_n, s_fp);
			}
			strncat(file_path, buf, b_size);
			path_n -= b_size;

		} while (path_n > 0);

		unsigned int data_s;
		b_size = fread(&data_s, 1, 4, s_fp);
		if (b_size != 4) {
			fprintf(stderr, "cannot read data with %s\n", file_path);
			exit(1);
		}
	
		if (mkdirs(dirname(file_path))) {
			fprintf(stderr, "ERROR: cannot mkdirs %s\n", dirname(file_path));
		}

		//printf("%s data size: %u\n", file_path, data_s);
		FILE * fp = fopen(file_path, "wb");
		do {
			char buf[512];
			if (data_s > 512) {
				b_size = fread(buf, 1, 512, s_fp);
			}
			else {
				b_size = fread(buf, 1, data_s, s_fp);
			}
			fwrite(buf, 1, b_size, fp);
			data_s = data_s - ((unsigned int)b_size);
		} while (data_s > 0);
		fclose(fp);
		free(file_path);

	} while (1);

	fclose(s_fp);

}
char *
parent_dir (char * path) {

	int lidx = strrchr(path, '/') - path;
	char * parent_dir_path = malloc(lidx * sizeof(char));
	strncpy(parent_dir_path, path, lidx);

	return parent_dir_path;
}

int 
mkdirs (char * dir_path) {

	char * p_dir;
	if (access(dir_path, F_OK) == 0) {
		/* already exists*/
		return 0;
	}
	else if (access((p_dir=parent_dir(dir_path)), F_OK) == 0) {
		free(p_dir);
		return mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	else {

		int val = mkdirs(p_dir) || mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		free(p_dir);
		return val;
	}
}
