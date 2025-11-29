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


/*
    Named Pipes

    “A named pipe is like a mailbox for processes — one process puts data in, and the other process takes it out, in the same order.”
    It’s commonly used for communication between unrelated processes in Linux.
    A FIFO (First In, First Out), also called a named pipe, is a type of inter-process communication (IPC) mechanism in Linux/Unix.

    - Named: Unlike regular pipes, a FIFO has a name in the filesystem and persists until deleted.
    - Communication: Allows two separate processes to send and receive data in a first-in, first-out order.
    - Direction: Can be read and written by different processes.
    - Blocking: If a process tries to read from an empty FIFO, it waits until data is written.

    amila@DESKTOP-0GI005N:~/ mkfifo myfifo_1
*/ 

int main(int argc, char* argv[])
{
    if(mkfifo("myfifo_1", 0777) == -1)
    {
        if(errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
    }

    // Opening the read or write end of a FIFO blocks until the other end is also opened by another process or thread
    // Both ends open at the same time
    printf("Opening...\n");
    // int fd = open("myfifo_1", O_WRONLY);
    int fd = open("myfifo_1", O_RDWR); // terminate because opened for both reading and writing
    if(fd == -1)
    {
        return 3;
    }

    printf("Opened\n");
    int x = 97;
    if(write(fd, &x, sizeof(x)) == -1)
    {
        return 2;
    }
    printf("Written\n");
    close(fd);
    printf("Closed\n");

    return 0;
}

