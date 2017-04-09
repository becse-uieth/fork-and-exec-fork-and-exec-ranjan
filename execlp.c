#include<stdio.h>
int main()
{
    int pid;
    pid=fork();
    if( pid == 0 )
    {
        printf("\nI am the child\n");
        execlp("/bin/ls","ls",NULL);
        perror("The execlp() call must have failed\n");

    }
    else if (pid > 0)
    {
        printf("\n I am the parent\n");
        wait();
    } 
}