/* When execvp() is executed, the program file given by the first argument will be loaded into the caller's address space and 
 over-write the program there. Then, the second argument will be provided to the program and starts the execution. 
 As a result, once the specified program file starts its execution, 
 the original program in the caller's address space is gone and is replaced by the new program.
 execvp() returns a negative value if the execution fails (e.g., the request file does not exist).*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(void) 
{
	pid_t child;
	int cstatus; 						/* Exit status of child. */
	pid_t c; 	
	int ret;
	char *cmd[] = { "ls", "-l", (char *)0 };						/* Pid of child to be returned by wait. */
	if ((child = fork()) == 0) 
	{									/* Child process. To begin with, it prints its pid. */
		printf("Child: PID of Child = %ld\n", (long) getpid());
										/* Child will now execute the ls command. */
		
		ret = execvp ("ls", cmd);

										/* If the child process reaches this point, then */
										/* execlp must have failed. */
		fprintf(stderr, "Child process could not do execvp.\n");
		exit(1);
	}
	else 
	{ /* Parent process. */
		if (child == (pid_t)(-1)) 
		{
			fprintf(stderr, "Fork failed.\n"); exit(1);
		}
		else 
		{
			c = wait(&cstatus); 		/* Wait for child to complete. */
			printf("Parent: Child %ld exited with status = %d\n", (long) c, cstatus);
		}
	}
	return 0;



