/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 1, part 1: Write a C program to implement a command called displaycontent 
	that takes a (text) file name as argument and display its contents. 
	Report an appropriate message if the file does not exist or can’t be opened
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    int fd;
    int rd;
    int ct;
    errno = 0;

    fd = open(argv[1], O_RDWR); // open argument file for read-writing

    // Check if file exist or not
    if (fd == -1)
    {
        printf("\n Error: [%s]\n", strerror(errno));
    }
    // if the file exist
    else
    {
        // Temp variable that stores the content of from the file
        char buf[BUFSIZ]; // Declare an array of char called buf that has a size of BUFSIZ (a macro constant)

        while ((rd = read(fd, buf, BUFSIZ)) > 0)
        {                      // rd is assigned the return value of read, which is the number of characters that are read from fd
            write(1, buf, rd); // write to the terminal whatever the 'read' syscall reads from the file
        }
    }
    close(fd);

    return 0;
}

/* Command

gcc part\ 1.c -o part_1
./part_1 source.txt 

*/