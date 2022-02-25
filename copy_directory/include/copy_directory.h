void
copy_directory (char * target_dir, char * destinated_dir);

void
copy(char * origin_path, char * copied_path, int is_dir);

void
path_recursive (char * target_dir, char * destinated_dir, char * sub_dir, void (*copy)(char*, char*, int));
