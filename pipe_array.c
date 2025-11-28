#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

// 2 processes
// 1) Child parent should generate random numbers and send them to the parent
// 2) Parent is going to sum all the numbers and print the result 

int main(int argc, char* argv[])
{
    int fd[2];
    if(pipe(fd) == -1)
    {
        printf("An error occured with opening the pipe\n");
        return 1;
    }

    int pid = fork();
    if (pid == -1)
    {
        printf("An error occured with fork\n");
        return 1;
    }

    if (pid == 0)
    {
        // child process 
        close(fd[0]);
        int n, i;
        int arr[10];
        srand(time(NULL));

        n = rand() % 10 + 1;
        for (i = 0 ; i < n ; i++)
        {
            arr[i] = rand() % 10;
        }

        if(write(fd[1], &n, sizeof(int)) < 0)
        {
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        printf("Sent n = %d\n", n);
        
        if(write(fd[1], arr, sizeof(int) * n) < 0)
        {
            printf("An error occured with writing to the pipe\n");
            return 2;
        }
        printf("Sent array\n");
        
        close(fd[1]);
    }else
    {
        // parent process
        close(fd[1]);
        // int *arr;
        // arr = (int*)malloc(sizeof(int) * 10);
        
        int arr[10];
        int n, i, sum=0;

        if(read(fd[0], &n, sizeof(int)) < 0)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }

        if(read(fd[0], arr, sizeof(int) * n) < 0)
        {
            printf("An error occured with reading from the pipe\n");
            return 3;
        }


        for(i = 0 ; i < n; i++)
        {
            sum += arr[i];
            printf("%d ", arr[i]);
        }

        printf("\nCalculate sum : %d\n", sum);
        wait(NULL); // Always remember to wait till the child process

        close(fd[0]);
    }

    return 0;
}