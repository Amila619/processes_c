#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int fd[2];
    if(pipe(fd) == -1)
    {
        return 2;
    }

    int pid = fork();
    if(pid == -1)
    {
        return 1;
    }

    if(pid == 0)
    {
        //child process
        close(fd[0]);

        char str[200];
        printf("Input String : ");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';
        int n = strlen(str) + 1; // including null character

        if(write(fd[1], &n, sizeof(int)) < 0)
        {
            return 3;
        }

        if(write(fd[1], str, sizeof(char) * n) < 0)
        {
            return 3;
        }

        printf("Sent %s from child process\n", str);
        close(fd[1]);
    }else
    {
        // parent process
        close(fd[1]);

        char str[200];
        int n;

        if(read(fd[0], &n, sizeof(int)) < 0)
        {
            return 4;
        }
        if(read(fd[0], str, n) < 0)
        {
            return 4;
        }

        printf("Received %s to parent\n", str);

        close(fd[0]);
        wait(NULL);
    }
    
    return 0;
}