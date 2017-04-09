#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>                         /*FIX: used to be <wait.h>*/
#include <stdlib.h>

int main() 
{
  sigset_t sigset;
  int    p[2], status;
  char   c='z';
  pid_t  pid;

  if (pipe(p) != 0)
    perror("pipe() error");
  else 
  {
    if ((pid = fork()) == 0) 
    {
      sigemptyset(&sigset);
      printf("child is letting parent know he's ready for signal\n");
      write(p[1], &c, 1);
      printf("child is waiting for signal\n");
      sigsuspend(&sigset);
      exit(0);
    }

    printf("parent is waiting for child to say he's ready for signal\n");
    read(p[0], &c, 1);
    printf("child has told parent he's ready for signal\n");

    kill(pid, SIGTERM);

    wait(&status);
    if (WIFSIGNALED(status))
    {
      if (WTERMSIG(status) == SIGTERM)
        printf("child was ended with a SIGTERM\n");
      else
        printf("child was ended with a %d signal\n", WTERMSIG(status));
    }
    else 
      printf("child was not ended with a signal\n");

    close(p[0]);
    close(p[1]);
  }
return 0;
}

