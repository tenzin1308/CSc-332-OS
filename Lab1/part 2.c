/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 1, part 2: Write a C program that mimics the cp command using open() 
	system call to open source.txt file in read-only mode and copy the 
	contents of it to destination.txt using read() and write() system calls
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
    int dest;

    errno = 0;

    // Open the source file in read-only mode
    fd = open(argv[1], O_RDONLY);

    dest = open(argv[2], O_CREAT | O_RDWR, S_IRWXU); // Open file and assign it to dest. If it does not exist, create it with read-write access

    if (fd == -1) // Check if the source file exist or not
    {
        printf("\n Error: [%s]\n", strerror(errno));
    }
    else
    {
        char buf[BUFSIZ];
        while ((rd = read(fd, buf, BUFSIZ)) > 0)
        { // While the number of characters read are greater than 0, write it into dest (second argument)
            write(dest, buf, rd);
        }
    }
    close(fd);
    close(dest);

    return 0;
}

/* Command

gcc part\ 2.c -o part_2
./part_2 source.txt (source) destination.txt (destination)

*/