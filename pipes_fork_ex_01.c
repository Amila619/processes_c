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

    if(pipe(fd) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    int id = fork();
    if(id == -1)
    {
        printf("An error occured with fork\n");
        return 4;
    }

    if(id == 0)
    {
        start = 0;
        end = arrSize / 2;
    }else
    {
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;
    int i;

    for(i = start ; i < end ; i++)
    {
        sum += arr[i];
    }

    printf("Calculated partial sum: %d\n", sum);

    if (id == 0)
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
        int psum;
        close(fd[1]);
        if(read(fd[0], &psum, sizeof(int)) == -1)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }
        close(fd[0]);

        int totalSum = psum + sum;
        printf("Calculated sum: %d\n", totalSum);
        wait(NULL); // wait for the child process to execute
    }

    return 0;
}