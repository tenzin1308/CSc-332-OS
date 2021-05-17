/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 3, part 3: Step 3. Fork a child process, say Child 1 and execute Process_P1. 
	This will create two destination files according to Step 1.
	Step 4. After Child 1 finishes its execution, fork another child process, 
	say Child 2 and execute Process_P2 that accomplishes the procedure described 
	in Step 2.
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
    int child_1, child_2;
    child_1 = fork();
    if (child_1 == 0)
    {
        // Child 1 Process
        printf("Child 1\n");
        execv(argv[1], NULL); // Execute Process_P1
        printf("EXECV Failed! Please first compile Process_P1.c \n");
    }
    else
    {
        sleep(1); // Wait for 1 second and fork a second child.
        child_2 = fork();

        if (child_2 == 0)
        {
            // Child 2 Process
            printf("Child 2\n");
            // char *const argv[] = {"pro_p1", NULL};
            execv(argv[2], NULL); // Execute Process_P2
            printf("EXECV Failed! Please first compile Process_P2.c \n");
        }
    }
    return 0;
}

/* Command
gcc Parent_Process.c -o parent_pro
./parent_pro pro_p1 (Process_P1) pro_p2 (Process_P2)
*/