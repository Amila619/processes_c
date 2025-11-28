#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    // 5 => 5 *4 => 20
    int p1[2], p2[2];

    if(pipe(p1) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    if(pipe(p2) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    int pid = fork();
    if(pid == -1)
    {
        printf("An error occured with fork\n");
        return 4;
    }

    if(pid == 0)
    {
        // child process
        close(p1[1]);
        close(p2[0]);

        int x;
        if (read(p1[0], &x, sizeof(x)) == -1)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }

        printf("Child Received %d\n", x);
        x *= 4;

        if (write(p2[1], &x, sizeof(x)) == -1)
        {
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        printf("Child Wrote %d\n", x);

    }else{
        // parent process

        close(p1[0]);
        close(p2[1]);

        srand(time(NULL));
        int y = rand() % 10;

        if (write(p1[1], &y, sizeof(y)) == -1)
        {
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        printf("Parent Wrote %d\n", y);

        if (read(p2[0], &y, sizeof(y)) == -1)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }

        printf("Parent Result is %d\n", y);

    }
    
    close(p1[0]);
    close(p2[1]);
    
    close(p1[1]);
    close(p2[0]);

    return 0;
}