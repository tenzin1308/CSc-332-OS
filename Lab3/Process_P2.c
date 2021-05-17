/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 3, part 3: Step 2. Copy the contents of source.txt1 into destination1.txt 
	and destination2.txt as per the following procedure.
	1. Read the next 50 characters from source.txt, and write it to destination1.txt
	2. Then the next 100 characters are read from source.txt, and written into destination2.txt.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int source, rd, dest1, dest2;
    source = open("source.txt", O_RDONLY);      // Open the source file.
    dest1 = open("destination1.txt", O_WRONLY); // Open destination1 and destination2.
    dest2 = open("destination2.txt", O_WRONLY);
    if (source == -1 || dest1 == -1 || dest2 == -1)
    {
        printf("Error: [%s]\n", strerror(errno));
    }
    else
    {
        char buf[101]; // Create an array of chars size 101 to read max of 101 chars.
        int n = 51;
        while ((rd = read(source, buf, n)) > 0)
        {
            if (n == 51)
            {
                write(dest1, buf, rd);
                n = 101;
            }
            else
            {
                write(dest2, buf, rd);
                n = 51;
            }
        }
    }
    close(source);
    close(dest1);
    close(dest2);

    return 0;
}