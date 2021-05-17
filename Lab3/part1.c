/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 3, part 1: Write a program where a child is created to execute command 
	that tells you the date and time in Unix. Use execl(...). Note, you need 
	to specify the full path of the file name that gives you date and time 
	information. Announce the successful forking of child process by displaying 
	its PID.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status, pid_child;
    pid_child = fork(); // Create a child
    wait(&status);
    if (pid_child == 0)
    {
        printf("I am child, my PID is: %d\n", getpid());
        execl("/bin/date", "date", NULL); // Prints out date and time in Unix.
        printf("EXECL Failed\n");         // Prints this line if above command isn't executed
    }
    else
    {
        printf("I am parent, my PID is: %d\n", getpid());
    }
    return 0;
}
