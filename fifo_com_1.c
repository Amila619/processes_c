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
    srand(time(NULL));
    int i;

    for(i = 0 ; i < 5 ; i++)
    {
        arr[i] = rand() % 100;
    }
    
    int fd = open("sum", O_WRONLY);
    if (fd == -1)
    {
        return 1;
    }
    
    for(i = 0 ; i < 5 ; i++)
    {
        if(write(fd, &arr[i], sizeof(int)) == -1)
        {
            return 2;
        }

        printf("Wrote %d\n", arr[i]);
    }

    close(fd);

    fd = open("sum", O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }

    int sum;
    if(read(fd, &sum, sizeof(int)) == -1)
    {
        return 2;
    }

    close(fd);
    printf("Sum of Number : %d\n", sum);


    return 0;
}

