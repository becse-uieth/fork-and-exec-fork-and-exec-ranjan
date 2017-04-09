#include <unistd.h>
int main()
{
   char *args[] = {"/bin/ls", "-r", "-t", "-l", (char *) 0 };
   execv("/bin/ls", args);
   return 0;
}
