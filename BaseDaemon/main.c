#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int
main(int argc, char* argv[])
{
    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;

    pid = fork();
    if (pid < 0)
    {
        printf("fork failed!\n");
        exit(1);
    }
    if (pid > 0)
    {
       printf("pid of child process %d \n", pid);
        exit(0);
    }

    umask(0);

    sid = setsid();
    if(sid < 0)
      exit(1);

    if ((chdir("/")) < 0)
      exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    for (;;)
      {
	fp = fopen ("mydaemonfile.txt", "a+");
	fputs("hi...\n", fp);
	fclose(fp);
        sleep(5);
      }

    return (0);
}
