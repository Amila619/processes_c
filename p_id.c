#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int id = fork();

    // If parent process gets terminated before child a new parent process assigned
    // Always wait before child process -> memory leak

    // if (id == 0)
    // {
    //     sleep(1);
    // }

    printf("Current ID : %d, parent ID: %d\n", getpid(), getppid());
    
    // find the child process which executed
    
    // int res = wait(NULL);
    // if(res == -1)
    // {
    //     printf("No children to wait for\n");
    // }else
    // {
    //     printf("%d finished execution\n", res);
    // }

    return 0;
}

/*

Current ID : 5001, parent ID : 5000   ← child (C, parent is P)
Current ID : 5000, parent ID : 4800   ← parent (P, parent is terminal)

*/ 