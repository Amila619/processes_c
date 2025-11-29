#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
    int arr[5];
    int fd = open("sum", O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }

    int i;
    for(i = 0 ; i < 5 ; i++)
    {
        if(read(fd, &arr[i], sizeof(int)) == -1)
        {
            return 2;
        }

        printf("Received %d\n", arr[i]);
    }

    int sum = 0;
    for(i = 0 ; i < 5 ; i++)
    {
        sum += arr[i];
    }

    close(fd);

    fd = open("sum", O_WRONLY);
    if (fd == -1)
    {
        return 1;
    }
    
    if(write(fd, &sum, sizeof(int)) == -1)
    {
        return 2;
    }

    close(fd);

    return 0;
}

