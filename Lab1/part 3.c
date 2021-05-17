/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 1, part 3: (a) Read the next 100 characters from source.txt, and among 
	characters read, replace each character ’1’ with character ’A’ 
	and all characters are then written in destination.txt
	(b) Write characters "XYZ" into file destination.txt
	(c) Repeat the previous steps until the end of file source.txt. 
	The last read step may not have 100 characters.
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
    int acs;
    int dest;

    fd = open(argv[1], O_RDONLY);

    dest = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);

    if (fd == -1)
    {
        printf("\n Error: [%s]\n", strerror(errno));
    }
    else
    {
        char buf[54];
        int rd;

        // While reading up to 50 chars, within every 50 chars
        //iterate through and it and if character '5' is scanned, replace with 'A'
        while ((rd = read(fd, buf, 53)) > 0)
        {
            for (int i = 0; i < rd; i++)
            {
                if (buf[i] == '5')
                    buf[i] = 'A';
            }

            //assign X,Y and Z to the array at index 50,51 and 52
            buf[rd] = 'X';
            buf[rd + 1] = 'Y';
            buf[rd + 2] = 'Z';

            write(dest, buf, rd + 3);
        }
    }

    close(fd);
    close(dest);

    return 0;
}
