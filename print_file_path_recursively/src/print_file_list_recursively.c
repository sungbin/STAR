#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "../include/print_file_list_recursively.h"

void
print_path_recursive (char * dir_name) {

        DIR * dp = opendir(dir_name);
        struct dirent *ep;

        if (dp != NULL)
        {
                while (ep = readdir(dp)) {
                        if (strcmp(ep->d_name,".") == 0) {
                                continue;
                        }
                        if (strcmp(ep->d_name,"..") == 0) {
                                continue;
                        }

                        if (ep->d_type == DT_DIR) {

                                int parrent_len = strlen(dir_name);
                                int child_len = strlen(ep->d_name);

                                //TODO: consider both path dividers (/, \\)
                                char * inner_dir_path = malloc(sizeof(char) * (parrent_len+child_len+1));
                                sprintf(inner_dir_path, "%s/%s",dir_name,ep->d_name);
                                printf(" \t DIR: %s\n", inner_dir_path);

                                print_path_recursive(inner_dir_path);
                                free(inner_dir_path);
                        } else {
                                printf(" \t FILE: %s/%s\n", dir_name, ep->d_name);
                        }
                }
                closedir(dp);
        }
        else {
                perror("Couldn't open the directory");
                exit(1);
        }

        closedir(dp);
}

