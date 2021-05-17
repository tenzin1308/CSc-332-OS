/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Task 2, part 2: Consider the parent process as P. The program consists of 
	fork() system call statements placed at different points in the code 
	to create new processes Q and R. The program also shows three variables: 
	a, b, and pid - with the print out of these variables occurring from 
	various processes. Show the values of pid, a, and b printed by the 
	processes P, Q, and R.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int a = 10, b = 25, fq = 0, fr = 0;
    fq = fork(); // fork a child - call it Process Q
    if (fq == 0)
    { // Child successfully forked
        a = a + b;
        //print values of a, b, and process_id
        printf("From the Q Process: \na = %d,\nb = %d, \nprocess_id = %d \n\n", a, b, getpid());
        fr = fork(); // fork another child - call it Process R
        if (fr != 0)
        {
            b = b + 15;
            //print values of a, b, and process_id
            printf("From the Q Process: \na = %d,\nb = %d, \nprocess_id = %d \n\n", a, b, getpid());
        }
        else
        {
            a = (a * b) + 20;
            //print values of a, b, and process_id
            printf("From the R Process: \na = %d,\nb = %d, \nprocess_id = %d \n\n", a, b, getpid());
        }
    }
    else
    {
        b = a + b - 5;
        printf("From the P Process: \na = %d,\nb = %d, \nprocess_id = %d \n\n", a, b, getpid());
    }
    return 0;
}