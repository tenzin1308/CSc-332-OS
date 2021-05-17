/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 3, part 2: Write a program where a child is created to execute a command 
	that shows all files (including hidden files) in a directory with 
	information such as permissions, owner, size, and when last modified.
	Use execvp(...). Announce the successful forking of child process by displaying its PID.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status, pid;
    pid = fork();
    wait(&status);
    if (pid == 0)
    {
        printf("I am child, my PID is: %d\n", getpid());
        // execlp("bin/ls","ls",NULL);
        char *argv[] = {"ls", "-lao", NULL};
        execvp(argv[0], argv);
        printf("EXECVP Failed\n");
    }
    else
    {
        wait(NULL);
        printf("I am parent, my PID is: %d\n", getpid());
    }

    return 0;
}
