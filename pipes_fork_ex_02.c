#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 3, 4, 1, 2, 7, 7};
    int arrSize = sizeof(arr) / sizeof(int);
    int fd[2];
    int start, end;
    int p1, p2;

    if(pipe(fd) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    p1 = fork();
    if(p1 == -1)
    {
        printf("An error occured with fork\n");
        return 4;
    }

    if(p1 == 0)
    {
        start = 0;
        end = arrSize / 2;
    }else
    {
        p2 = fork();
        if(p2 == -1)
        {
            printf("An error occured with fork\n");
            return 4;
        }

        if (p2 == 0) {
            start = arrSize / 2;
            end = arrSize;
        }
    }

    int sum = 0;
    int i;

    for(i = start ; i < end ; i++)
    {
        sum += arr[i];
    }

    if(p1 == 0 || p2 == 0)
    {
        printf("Calculated partial sum: %d\n", sum);
    }

    if (p1 == 0)
    {
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(int)) == -1)
        {
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        close(fd[1]);
    }else if (p2 == 0)
    {
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(int)) == -1)
        {
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        close(fd[1]);
    }else
    {
        int total, sum1, sum2;
        close(fd[1]);
        if(read(fd[0], &sum1, sizeof(int)) == -1)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }

        if(read(fd[0], &sum2, sizeof(int)) == -1)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }
        close(fd[0]);

        total = sum1 + sum2;

        printf("Calculated sum: %d\n", total);

        // The standard wait(NULL) waits for any child to finish, does not take a process id

        waitpid(p1, NULL, 0);  // wait for child 1
        waitpid(p2, NULL, 0);  // wait for child 2
    }

    return 0;
}