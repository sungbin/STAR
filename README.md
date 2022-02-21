# STAR: Simple TAR-file archiving program

## proplems
(1) Read and write a file as binary (not as test)
  - What's the other file interfaces that read and write a file as text?
```C
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
ssize_t pread(int d, void *buf, size_t nbyte, off_t offset), pwrite;
ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);
int aio_read(struct aiocb *aiocbp);
int aio_write(struct aiocb *aiocbp);
```
  
  - How accessing a file as binary is different from accessing it as text?
```
The minumum units which are read/written by function call are different which other.
For example, fread() read n-items, and read() read n-bytes.
```

  - Write a program that shows each byte of a given file as a hexadecimal number (like xxd does)
<blockquote>(on-going) https://github.com/sungbin/STAR/tree/main/byte_to_hexa</blockquote>

(2) Aceessing a directory
  - What is the _path_ of a file? How it is different from the _name_ of a file?
<blockquote>
A path of a file contains its parent directory structure from root or to relative path. A name of a file is the name of a file in directory hierarchy.
</blockquote>

  - Write a program that enumerates the paths of all files under a given directory and its subdirectories recursively
<blockquote>(on-going) https://github.com/sungbin/STAR/tree/main/copy_directory</blockquote>

  - Write a program that copies the entire files and the directory structrue of a given path to another specified path
<blockquote>(on-going) https://github.com/sungbin/STAR/tree/main/files_path_recursive</blockquote>

(3) Retrieving file attribute
  - What is a regular file? How one can check if a file is a regular file or not?
<blockquote>
Any file that contains bytes of data into a specifie format is reguar file.
</blockquote>

  - How one can find the size of a file?
