#include <stdio.h>
#include <sys/wait.h>            
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int main() 
{
  pid_t pid;
  int status;

  if ((pid = fork()) == 0) 
  {
    execl("/bin/false", NULL);
    perror("The execl() call must have failed");
    exit(255);
  }
  else 
  {
    wait(&status);
    if (WIFEXITED(status))
      printf("child exited with status of %d\n", WEXITSTATUS(status));
    else
      printf("child did not exit successfully\n");
  }
}