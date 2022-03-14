void
path_recursive (char * target_dir, char * destinated_dir, char * sub_dir, void (*copy)(char*, char*, int));

void
archive (char * star_path, char * destinated_dir_path);

void
list (char * star_path);

void
extract (char * star_path);
