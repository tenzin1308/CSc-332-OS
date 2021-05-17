/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 2, part 1: Write a program processes.c , and let the parent process produce    two child processes. One prints out "I am first child, my pid is: " PID, and the other prints out "I am second child, my pid is: "
PID.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int pid_1, pid_2;
    pid_1 = fork(); // Create the first child

    if (pid_1 == 0)
    {
        printf("I am first child, my PID is: %d\n", getpid());
        pid_2 = fork(); // Create the second child
        if (pid_2 == 0)
        {
            printf("I am second child, my PID is: %d\n", getpid());
        }
    }
    else
    {
        printf("I am the parent, my PID is: %d\n", getpid());
    }

    return 0;
}