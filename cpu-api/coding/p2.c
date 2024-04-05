#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int file = open("file", O_RDWR);
    int p = fork();
    if (p < 0) {
        printf("fork failed");
    }
    else if (p == 0)
    {
        // child process
        write(file, "Child\n", 6);
    }
    else
    {
        // parent process
        write(file, "Parent\n", 7);
    }
}
