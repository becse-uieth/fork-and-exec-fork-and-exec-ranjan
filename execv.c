#include<stdio.h>
int main()
{
    int pid;
    pid=fork();
    if( pid == 0 )
    {
        printf("\nI am the child\n");
        char *args[] = {"/bin/ls", "-r", "-t", "-l", (char *) 0 };
        execve("/bin/ls", args);
        perror("The execlp() call must have failed\n");

    }
    else if (pid > 0)
    {
        printf("\n I am the parent\n");
        wait();
    } 
}
