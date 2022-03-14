# STAR: Simple TAR-file archiving program

## proplems
(1) Read and write a file as binary (not as test)
+ __fread()__ : <http://www.cplusplus.com/reference/cstdio/fread/>  
+ __fwrite()__ : <http://www.cplusplus.com/reference/cstdio/fwrite/>  
+ What's the other file interfaces that read and write a file as text?  
```C
fgetc(3), getc(3), getchar(3) - get next character or word from input stream
fgetln(3)                - get a line from a stream
fgets(3), gets(3)        - get a line from a stream
fputc
fputs
```
+ How accessing a file as binary is defferent from accessing it as text?  
<blockquote>
The minumum units which are read/written by function call are different each other. For example, fread() read n-items(char, string), and read() read n-bytes.

ELF that is standard binary file format in unix system contains not only text data but also the additional meta data (like ELF header header table..). When accessing a ELF format file, must consider such format.
</blockquote>

+ Write a program that shows each byte of a given file as a hexadecimal number (like xxd does) 
<blockquote> https://github.com/sungbin/STAR/tree/main/byte_to_hexa</blockquote>

(2) Aceessing a directory
+ Opening a directory  <https://www.gnu.org/software/libc/manual/html_node/Opening-a-Directory.html>

+ Reading a directroy  <https://www.gnu.org/software/libc/manual/html_node/Reading_002fClosing-Directory.html>
  
+ Simple directory lister  <https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html>  

+ What is the _path_ of a file? How it is different from the _name_ of a file?  
<blockquote>
A path of a file contains its parent directory structure from root or to relative path. A name of a file is the name of a file in its parrent directory hierarchy.
</blockquote>

+ Write a program that enumerates the paths of all files under a given directory and its subdirectories recursively.  
<blockquote> https://github.com/sungbin/STAR/tree/main/print_file_path_recursively</blockquote>

+ Write a program that copies the entire files and the directory structure of a given path to another specified path.  
<blockquote> https://github.com/sungbin/STAR/tree/main/copy_directory</blockquote>

(3) Retrieving file attribute
+ Stat System call <https://linuxhint.com/stat-system-call-linux/>
+ What is a regular file? How one can check if a file is a regular file or not?

  - Linux File System administrate file-path and file-data (including metadata) relative to the file-path. Metadata contains information determine whether it is regular or not.

+ How one can find the size of a file?
  - _stat_(2), _fstat(2)_ look into the file information with file size.
